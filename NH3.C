/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "NH3.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(NH3, 0);
    addToRunTimeSelectionTable(liquidProperties, NH3,);
    addToRunTimeSelectionTable(liquidProperties, NH3, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::NH3::NH3()
:
    liquidProperties
    (
        17.031,
        405.5,
        1.13e7,
        0.07247,
        0.2429,
        195.4,
        6.060e+2,
        239.8,
        4.9234e-30,
        0.253,
        2.9217e+04
    ),
    rho_(6.0341E+01, 2.5471e-01, 405.5, 2.8870e-01),
    pv_(9.0451e+01, -4.6690e+03, -1.1601e+01, 1.7183e-02, 1),
    hl_(405.5, 1.8509E+06, 3.9140e-01, -2.2890e-01, 2.3090e-01, 0),
    Cp_
    (
	6.3572E+04,
	-9.1251E+02,
	5.2264E+00,
	-1.3219E-02,
	1.2528E-05,
        0
    ),
    h_
    (
        -7.0700E+06,
      	6.3572E+04,
	-4.5626E+02,
	1.7421E+00,
	-3.3047E-03,
	2.5055E-06
    ),
    Cpg_(1.94891E+03, 4.35878E+03, 5.40400E+02, 8.89500E-01),
    B_
    (
        1.5600e-02, 
       -1.9900e+01, 
       -5.0500e+06, 
       -2.5330e+18,
        3.8700e+20
    ),
    mu_(-1.6430e+00, 4.5560e+02, -1.5637e+00, 0, 0),
    mug_(4.1855e-08, 9.8060e-01, 3.0800e+01, 0),
    kappa_(1.1606e+00, -2.2840e-03, 0, 0, 0, 0),
    kappag_(-4.5900e-02, 1.6520e-01, -1.7078e+03, 0),
    sigma_(9.1200e-02, 1.1028e+00, 0, 0, 0, 0),
    D_(14.9, 20.1, 17.03, 28)
{}


Foam::NH3::NH3
(
    const liquidProperties& l,
    const NSRDSfunc5& density,
    const NSRDSfunc1& vapourPressure,
    const NSRDSfunc6& heatOfVapourisation,
    const NSRDSfunc0& heatCapacity,
    const NSRDSfunc0& enthalpy,
    const NSRDSfunc3& idealGasHeatCapacity,
    const NSRDSfunc4& secondVirialCoeff,
    const NSRDSfunc1& dynamicViscosity,
    const NSRDSfunc2& vapourDynamicViscosity,
    const NSRDSfunc0& thermalConductivity,
    const NSRDSfunc2& vapourThermalConductivity,
    const NSRDSfunc6& surfaceTension,
    const APIdiffCoefFunc& vapourDiffussivity
)
:
    liquidProperties(l),
    rho_(density),
    pv_(vapourPressure),
    hl_(heatOfVapourisation),
    Cp_(heatCapacity),
    h_(enthalpy),
    Cpg_(idealGasHeatCapacity),
    B_(secondVirialCoeff),
    mu_(dynamicViscosity),
    mug_(vapourDynamicViscosity),
    kappa_(thermalConductivity),
    kappag_(vapourThermalConductivity),
    sigma_(surfaceTension),
    D_(vapourDiffussivity)
{}


Foam::NH3::NH3(const dictionary& dict)
:
    NH3()
{
    readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::NH3::writeData(Ostream& os) const
{
    liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream& os, const NH3& l)
{
    l.writeData(os);
    return os;
}


// ************************************************************************* //
