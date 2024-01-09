#pragma once

namespace Physique{

    //constantes obligatoires pour les différents calculs de cube d'air
    constexpr static double g(9.81);//gravite
    constexpr static double R(8.3144621);//constante gaz parfait
    constexpr static double M_air_sec(0.02896);//masse molaire de l'air sec
    constexpr static double P_ref(101325);
    constexpr static double M_eau(0.0180153);//masse molaire de la vapeur d'eau

    //Mise des différentes constantes (à fixer au début du programme) ici car plus facile à modifier que d'aller les chercher dans tout le programme
    constexpr static double delta (0.017); //facteur de diminution du taux d'humidité
    constexpr static double delta_prime (0.05); //valeur d'augmentation du taux d'humidité
    constexpr static double dt(0.031); //pas de temps
    constexpr static double pression_equilibre(0.0083); //Modifier ici la pression d'équilibre voulue
    constexpr static double delta_pluie (0.05); //pourcentage auquel on diminue le taux d'humidité s'il y a de la pluie à modifier dans ce fichier.
}

