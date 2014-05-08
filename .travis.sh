sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get -qq update
sudo apt-get install llvm
sudo apt-get -qq install libstdc++-4.8-dev
clang++ --version && make && ./utests
