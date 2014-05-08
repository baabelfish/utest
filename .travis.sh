sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get -qq update
# sudo apt-get install llvm
make && ./utests
