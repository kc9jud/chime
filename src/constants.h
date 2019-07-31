#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
  constexpr double pi = 3.1415926535897932384626433832795028841971693993751;
  constexpr double sqrtpi = 1.7724538509055160272981674833411451827975494561224;
  constexpr double sqrt2 = 1.4142135623730950488016887242096980785696718753769;

  // Conversion Factor
  constexpr double hbarc = 197.3269602; // (in MeV fm)
  constexpr double hbarc_GeV = 0.1973269602; // (in GeV fm)

  // Masses
  constexpr double pion_mass_MeV = 134.9770;
  constexpr double pion_mass_fm = pion_mass_MeV / hbarc; // (in fm^{-1})
  constexpr double reduced_nucleon_mass_MeV = 469.4593340;
  constexpr double reduced_nucleon_mass_fm = reduced_nucleon_mass_MeV / hbarc;
  constexpr double nucleon_mass_MeV = reduced_nucleon_mass_MeV * 2;
  constexpr double nucleon_mass_fm = reduced_nucleon_mass_fm * 2;
  constexpr double nuclear_magneton_MeV = 1.0 / (nucleon_mass_MeV * 2); // (e = 1)
  constexpr double nuclear_magneton_fm = 1.0 / (nucleon_mass_fm * 2); // (e = 1)

  // Low energy constants
  constexpr double isoscalar_nucleon_charge_radius_sq_fm = 0.603729; // (in fm^2)
  constexpr double isoscalar_nucleon_magnetic_moment = 0.88;
  constexpr double isovector_nucleon_magnetic_moment = 4.706;
  constexpr double gA = 1.25;
  constexpr double pion_decay_constant_MeV = 92.4;
  constexpr double pion_decay_constant_fm = pion_decay_constant_MeV / hbarc; // (in fm^{-1})
  constexpr double d9_GeV = -0.011; // (in GeV^{-2})
  constexpr double d9_fm = d9_GeV * hbarc_GeV * hbarc_GeV; // (in fm^2)
  constexpr double d18_Gev = -10.14; // (in GeV^{-2})
  constexpr double d18_fm = d18_Gev * hbarc_GeV * hbarc_GeV; // (in fm^2)
  constexpr double L2_GeV = 0.188; // (in GeV^{-4})
  constexpr double L2_fm = L2_GeV * hbarc_GeV * hbarc_GeV * hbarc_GeV * hbarc_GeV; // (in fm^4)
}

#endif
