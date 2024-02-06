# Nucleon Momentum Distribution in a Deuteron

This repository provides the C++ source code for calculating the momentum distribution of nucleons inside a deuteron. 
The calculations incorporate parameters from the [Paris](https://doi.org/10.1016/0370-2693(81)90659-6) and the [charge-dependent Bonn](https://doi.org/10.1103/PhysRevC.63.024001) nucleon-nucleon potentials.

## Software Dependencies

The codebase is built upon the [ROOT](https://root.cern) data analysis framework, renowned for its robust processing and visualization capabilities in particle physics and beyond. 
Additionally, the project includes the `json.hpp` header from the [nlohmann/json](https://github.com/nlohmann/json) library, located in the `include` directory for JSON parsing.

## Environment Setup

Before compiling and running the calculations, ensure that the `ROOTSYS` environment variable is correctly set to the ROOT framework's installation directory.

## Compilation and Execution

To build and execute the calculations, execute the following commands:

```bash
# Clone the repository to your local machine
git clone https://github.com/alex-nuclearboy/nucleon-momentum-distribution.git

# Navigate to the repository directory
cd nucleon-momentum-distribution/deuteron

# Create a build directory and navigate into it
mkdir build && cd build

# Generate Makefile and build the project
cmake .. && make

# Return to the project root directory
cd ..

# Execute the calculations
./momentum_distribution
```

## Outputs

The software generates output files, including calculated momentum distribution data in txt format and associated graphs in png`format. 
These files can be found in the `data` and `plots` directories, respectively.

## References

[1] M. Lacombe et al., "Parametrization of the deuteron wave function of the Paris N-N potential". Phys. Lett. B **101** (1981), 139-140. [DOI: 10.1016/0370-2693(81)90659-6](https://doi.org/10.1016/0370-2693(81)90659-6)

[2] R. Machleidt, "The high-precision, charge-dependent Bonn nucleon-nucleon potential". Phys. Rev. C **63** (2000), 024001. [DOI: 10.1103/PhysRevC.63.024001](https://doi.org/10.1103/PhysRevC.63.024001)

## License
This project is licensed under the GNU General Public License version 3.0 (GPL-3.0). For details, please refer to the LICENSE file.

