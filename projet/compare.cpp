/* ======================================================================
 * Compares two files. See usage() below.
 *
 * Auteur : J.-C. Chappelier
 * Version 2021-04-01.1
 * (c) EPFL 2021
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <string>
#include <string_view>
#include <cstdlib>
#include <cerrno>
#include <cfloat>
#include <cassert>
using namespace std;

constexpr double default_precision(1e-12);

typedef array<double, 3> Data;
typedef array<size_t, 3> Indices;

// ======================================================================
// equality between indices
void usage()
{
  cout << R"(utilisation : compare filename1 filename2 [precision]

Compare, à une précison donnée, 2 fichiers « allignés » (expliqué ci-dessous)
de vecteurs de 1D à 3D.

Le format de chaque fichier doit être :
i j k vx vy vz
où i, j et k sont 3 entiers et vx, vy, vz les coordonnées de chaque vecteur
  (il peut y en avoir de 1 à 3).

« Allignés » signifie que les 2 fichiers ont les mêmes triplets i, j, k
aux mêmes lignes.

Les paramètres à passer au programme sont les 2 noms de fichiers
et éventuellement la précision de comparaison ()";
  cout << default_precision;
  cout << R"( par défaut).

Par exemple :
  compare testPotentiel2-lapl.dat monfichier.txt
  compare fichier1 fichier2 1e-3

Exemple de fichier à comparer (3 indices et 2 données ici) :
1 1 1 0.3 0.4
1 1 2 0.7 -0.33
)";
}

// ======================================================================
// equality between indices
bool operator==(Indices const& a, Indices const& b)
{
  assert(a.size() >= 3); // in case someone changes Indices type
  assert(b.size() >= 3);

  return (a[0] == b[0]) and (a[1] == b[1]) and (a[2] == b[2]);
}

// ======================================================================
// Handles need I/O
class File
{
public:
  File(const char* filename);
  ~File() { access_.close(); }
  File(const File&)            = delete;
  File& operator=(const File&) = delete;
  File(File&&)            = default;
  File& operator=(File&&) = default;
  
  bool read_line();

  int         eof()    const { return access_.eof(); }
  size_t      line_nb() const { return line_nb_     ; }
  string_view line()    const { return current_line_; }

  bool is_aligned_with(File const& other) const
  { return current_indices_ == other.current_indices_; }

  size_t data_are_equal_until(File const& other, double precision) const;

private:
  bool parse_line();

  ifstream access_;
  string current_line_;
  size_t line_nb_;
  Data current_data_;
  Indices current_indices_;
};

// ======================================================================
// opens a file for reading (with appropriate error message, if any)
// Throws on failure
File::File(const char* filename)
  : access_(filename), line_nb_(0)
  , current_data_({{0.0}})
  , current_indices_({{0, 0, 0}})
{
  if (access_.fail()) {
    cerr << "ERREUR : impossible d'ouvrir le fichier \""
         << filename << "\" en lecture." << endl;
    throw 42; // whatever
  }
}

// ======================================================================
// reads one line from the file
bool File::read_line()
{
  bool return_value(true);
  if (not eof()) {
    getline(access_, current_line_);
    if (access_.fail()) {
      return_value = false;
    } else {
      ++line_nb_;
      return_value = parse_line();
    }
  } else {
    current_line_.clear();
  }
  return return_value;
}

// ======================================================================
// parses one read line, into data
bool File::parse_line()
{
  assert(current_indices_.size() >= 3); // in case someone changes Indices type

  stringstream to_read(current_line_);
  if (not (to_read >> current_indices_[0]
                   >> current_indices_[1]
                   >> current_indices_[2]))
    return false;

  size_t i(0);
  while ((i < current_data_.size())
         and (to_read >> current_data_[i++]));
  return true;
}

// ======================================================================
// returns first component where two Data differ more than precisions.
// returns v1.size() if both match.
size_t File::data_are_equal_until(File const& other, double precision) const
{
  assert(current_data_.size() == other.current_data_.size()); // in case someone changes Data type for a dynamic type

  for(size_t i(0); i < current_data_.size(); ++i) {
    if (abs(current_data_[i] - other.current_data_[i]) > precision) return i;
  }
  return current_data_.size();
}

// ======================================================================
// check if same line matches between file1 and file2
bool match(File& file1, File& file2, double precision)
{
  bool return_value(true);

  if (file1.read_line() and file2.read_line()) {
    
    if (not file1.is_aligned_with(file2)) {
      return_value = false;
      cout << "Les deux fichiers ne sont pas alignés, ligne " << file1.line_nb()
           << " :" << endl;
      cout << "fichier 1 : " << file1.line() << endl;
      cout << "fichier 2 : " << file2.line() << endl;

    } else {
      const size_t component = file1.data_are_equal_until(file2, precision);
      if (component < tuple_size<Data>::value) { // stupid dirty hack because array::size() is not static :-(

        // This is NOT a failure, just a warning (so as not to stop further comparison)
        cout << "Les deux fichiers diffèrent composante " << (component + 1)
             << " de la ligne " << file1.line_nb() << " :" << endl;
        cout << "fichier 1 : " << file1.line() << endl;
        cout << "fichier 2 : " << file2.line() << endl;
      }
    }
 
  } else { // cannot read line in one of the two files
    return_value = false;
  }
  
  return return_value;
}

// ======================================================================
// compare two files
int compare(const char* filename1, const char* filename2
            , double precision)
{
  try {
    File file1(filename1);
    File file2(filename2);

    while (match(file1, file2, precision));
  
    // we don't care if one to the two files is too long
    return (file1.eof() or file2.eof() ? EXIT_SUCCESS : EXIT_FAILURE);

  } catch(...) {
    return EXIT_FAILURE;
  }
}

// ======================================================================
// Fail-safe char* to double conversion
double convert(const char* s)
{
  char* end(nullptr);
  errno = 0;
  const double value(strtod(s, &end));

  // Error cases. These are indeed double equality tests.
  if (   (    (errno == ERANGE)
          and ((value == DBL_MAX) or (value == -DBL_MAX)))
      or ((errno != 0) and (value == 0.0))
      or (end == s))
    throw 42; // whatever

  return value;
}

// ======================================================================
int main(int argc, char** argv)
{
  if (argc < 3) {
    cerr << "ERREUR: pas assez d'arguments." << endl;
    usage();
    return EXIT_FAILURE;
  }

  double precision(default_precision);
  if (argc >= 4) {
    try {
      precision = convert(argv[3]);
    } catch (...) {
      usage();
      return EXIT_FAILURE;
    }
  }
  
  return compare(argv[1], argv[2], precision);
}
