# CCDSALG Project 1

### OVERALL
- [COMPLETE] Identify 2 more sorting algorithms
- [COMPLETE] Assign Algorithms to Group Members
- [COMPLETE] Research Code Snippets & Study Their Implementation
- [COMPLETE] Modify Source Codes As Specified
- [ONGOING] Testing Phase
- [ONGOING] Documentation

## Testing Phase
Testing phase is currently ongoing. If you wish to also do some testing, you may download the executable binary file from Github's releases section. Great work!

## Test Status
- [Main System] : Preparing to Start
- [Backup 1] : Preparing to Start
- [Backup 2] : Standby

### Testing Guidelines
The driver code is setup to run the test automatically, using the settings for CCDSALG specifications (N from 1024 to 500k; M = 12). Results are automatically calculated and tallied to a CSV file named "OutputData.csv". **It is incredibly important to note that the file must be renamed before every test**. 
Every test is automated. Once it starts, there is no need for any user input.

### Testing Duration
The test might last a maximum of one entire week. Having M = 20 and N = 2 million took about 7 days (bubble sort & quick sort). With the addition of all the sorting algortihms, there is a possibility that testing would take the same time or even longer, even with reduced N and M values.

### Testing Machine Specifications

#### Main Testing System - DigitalOcean Server Droplet
Operating System: Ubuntu 20.04 LTS
CPU: 2 KVM Virtualized Cores
Memory: 2GB RAM
Storage: SSD

#### Backup Testing System 1 - Raspberry Pi 3
Operating System: Raspbian Jessie (Debian Based)
CPU: ARM64 Based Processor (Quad Core)
Memory: Onboard 4GB RAM
Storage: 64GB Class 10 SD Card

#### Backup Testing System 2 (Last Resort) - Custom PC
Operating System: Windows 10
CPU: AMD A10 - 4 Cores 8 Threads
Memory: 8GB HyperX DDR3
Storage: 4TB SATA HDD
