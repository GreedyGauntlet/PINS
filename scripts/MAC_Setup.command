# get directory where script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# change current directory to the script's directory
cd "$SCRIPT_DIR"

pushd ..
./vendor/premake/bin/MACpremake5 xcode4
popd
read -n 1 -s -r -p "Press any key to continue..."