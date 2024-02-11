# Nucleon and N\* Resonance Momentum Distribution Analysis

[Key Features](#key-features) · [Software Dependencies](#software-dependencies) · [Environment Setup](#environment-setup) · [Compilation and Execution](#compilation-and-execution) · [Outputs](#outputs) · [References](#references) · [License](#license)

This repository provides analytical tools for investigating the momentum distribution of nucleons within a deuteron as well as the momentum distribution of the N\*(1535) resonance within the <sup>3</sup>He nucleus.

It uses different nucleon-nucleon interaction models, specifically the Paris [[1](<https://doi.org/10.1016/0370-2693(81)90659-6>)] and the charge-dependent Bonn (CD-Bonn) [[2](https://doi.org/10.1103/PhysRevC.63.024001)] potentials, to calculate and visually represent the nucleon momentum distribution in a deuteron. The process is streamlined by the software automatically processing model parameters provided in a JSON configuration file, resulting in both numerical data and graphical representations of the momentum distributions.
The calculated nucleon momentum distribution in the deuteron allows simulating and analysing quasi-elastic proton and deuteron scattering reactions (pd -> ppn<sub>spectator</sub>).

Additionally, the repository includes the tool for graphical representation of the momentum distribution of the N\* resonance within the <sup>3</sup>He nucleus, considered as a bound system of the resonance and a deuteron. This analysis is based on the theoretical work of Kelkar _et al._ [[3](https://doi.org/10.1142/S0218301319500666)], [[4](https://doi.org/10.1016/j.nuclphysa.2020.121698)], in which the N\* momentum distribution is evaluated for various sets of coupling constants corresponding to binding energies E<sub>N\*-d</sub> = -0.33, -0.53, and -0.74 MeV. 
The tool's ability to compare these distributions with proton momentum distributions in <sup>3</sup>He is crucial for simulating and exploring the production and decay mechanisms of η-mesic helium nuclei.

These momentum distributions can be used in conjunction with the simulation tools available in the [WASA-Simulations](https://github.com/alex-nuclearboy/WASA-Simulations) repository to perform comprehensive nuclear reaction simulations.

## Key Features

-   **Deuteron Analysis:** Uses Paris [[1](<https://doi.org/10.1016/0370-2693(81)90659-6>)] and CD-Bonn [[2](https://doi.org/10.1103/PhysRevC.63.024001)] nucleon-nucleon potentials for calculations of nucleon momentum distribution in a deuteron, derived from parameters specified in a JSON configuration file.
-   **N\*(1535) Resonance in <sup>3</sup>He:** The tool converts N\* momentum values from fm<sup>-1</sup> to GeV/c and normalises the distribution, facilitating the visualisation of the N\* momentum distribution within the <sup>3</sup>He nucleus. Additionally, it provides comparative visualisations of proton momentum distributions in <sup>3</sup>He.

## Software Dependencies

The codebase is built upon the [ROOT](https://root.cern) data analysis framework, renowned for its powerful processing and visualisation capabilities in particle physics and beyond.
Additionally, the project includes the `json.hpp` header from the [nlohmann/json](https://github.com/nlohmann/json) library, located in the `include` directory for JSON parsing.

## Environment Setup

Before compiling and running the application, ensure that the `ROOTSYS` environment variable is correctly set to the ROOT framework's installation directory.

## Compilation and Execution

To build and execute the calculations, execute the following commands:

```bash
# Clone the repository to your local machine
git clone https://github.com/alex-nuclearboy/nucleon-momentum-distribution.git

# Navigate to the repository directory
cd nucleon-momentum-distribution

# Create a build directory and navigate into it
mkdir build && cd build

# Use CMake to configure and build the project:
cmake .. && make

# Return to the project root directory
cd ..

# Execute the generated binaries
./deuteron_momentum_distribution
./helium_momentum_distribution
```

## Outputs

The software produces text files detailing nucleon momentum distributions in a deuteron and text files with the N\* resonance's momentum distributions in <sup>3</sup>He, converted from from fm<sup>-1</sup> to GeV/ and normalised. These files are saved in the `data` folder. Graphical outputs are stored as images in the `plots` folder.

## References

[1] M. Lacombe _et al._, "Parametrization of the deuteron wave function of the Paris N-N potential". _Phys. Lett. B_ **101** (1981) 139-140. [DOI: 10.1016/0370-2693(81)90659-6](<https://doi.org/10.1016/0370-2693(81)90659-6>).

[2] R. Machleidt, "The high-precision, charge-dependent Bonn nucleon-nucleon potential". _Phys. Rev. C_ **63** (2000) 024001. [DOI: 10.1103/PhysRevC.63.024001](https://doi.org/10.1103/PhysRevC.63.024001).

[3] N. G. Kelkar _et al._, "N-N-N\* model calculations for experimental η-mesic <sup>3</sup>He searches". _Int. Jour. Mod. Phys. E_ **28** (2019) 1950066. [DOI: 10.1142/S0218301319500666](https://doi.org/10.1142/S0218301319500666).

[4] N. G. Kelkar _et al._, "Study of the N\* momentum distribution for experimental η-mesic <sup>3</sup>He searches". _Nucl. Phys. A_ **996** (2020) 121698. [DOI: 10.1016/j.nuclphysa.2020.121698](https://doi.org/10.1016/j.nuclphysa.2020.121698).

## License

This project is distributed under the [GNU General Public License version 3.0 (GPL-3.0)](https://www.gnu.org/licenses/gpl-3.0.en.html). For details, please refer to the LICENSE file.

[Back to Top](#nucleon-and-n-resonance-momentum-distribution-analysis)
