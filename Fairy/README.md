Project name:
Fairy

Name(s) of contributors:
Genisa Salinas and Santiago Jimenez

What your program will do: 
The program will display a digital companion that will interact with the user. It will have many tasks such as keeping track of the time, displaying motivational messages, showing the weather and temperature with corresponding clothing, having the ability to talk (will add in the future ... hopefully), showing different facial expressions depending on the battery health, or a login count. It
also has a secret event depending if it lands on a specific day.

Why the program is useful: 
This type of system will give people the ability to check the weather and get a quick boost of motivation in one quick glance
whereas using a phone can often lead to other unintended applications. This device will
also have the ability to speak making it have less of a robot feel (will add in the future ... hopefully). The character will also
be adorable to keep users engaged for their short duration of usage. Also, we will have
a system where it keeps track of the days logged in to encourage players to continue
playing.

Steps to run and compile: (AI helped me make these steps and recommened this layout)
## Requirements:
Before compiling you will need to install the following:

### macOS:
Install Homebrew if you do not have it:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Then install raylib and curl:
```bash
brew install raylib
brew install curl
```

### Linux:
```bash
sudo apt install libraylib-dev libcurl4-openssl-dev
```

### Windows:
Download and install raylib from https://www.raylib.com and curl from https://curl.se.
Make sure MinGW is installed for the g++ compiler.

## How to compile and run:

### Step 1 - Navigate to your project folder
Open your terminal and cd into wherever your project lives:
```bash
cd /path/to/your/Fairy/project
```
Make sure your assets folder and data folder are in the same directory as your .cpp files.


### Step 2 - Create the data folder if it does not exist
```bash
mkdir -p data
```

### Step 3 - Compile
```bash
make
```

### Step 4 - Run
```bash
make run
```

### Step 5 - Clean (optional, removes compiled files)
```bash
make clean
```

### Option 2 - VS Code (easier for beginners)

#### Step 1 - Install VS Code
Download and install VS Code from https://code.visualstudio.com if you do not have it.

#### Step 2 - Open your project folder
In VS Code go to File → Open Folder and select your Fairy project folder.

#### Step 3 - Install the C/C++ extension
Go to the Extensions tab on the left sidebar and search for "C/C++" by Microsoft and install it.

#### Step 4 - Open the terminal inside VS Code
Go to Terminal → New Terminal at the top menu bar. This opens a terminal already
pointed at your project folder so you do not need to cd into it.

#### Step 5 - Run the same make commands from there
```bash
make
make run
```

Using VS Code this way gives you the benefit of syntax highlighting, error highlighting,
and a built in terminal all in one place without needing to leave the application.

## Notes:
- The program automatically reads your computer's real battery percentage.
- The Makefile automatically detects if you are on an Apple Silicon Mac (M1/M2/M3),
  an Intel Mac, Linux, or Windows and adjusts paths accordingly.
- Weather is fetched from the NWS API and updates once per hour.
- The motivational message changes every time you run the program.
- Login count is saved to data/saveFile.txt and increments once per day.

Features of the program:
This follows the same idea as what the program will do. You will see motivational messages, a companion, be able to check weather and time.

Data structures used:
The data structures we used were vectors, strings, and map. 

The vectors stores a list of strings containing our motivational messages. We chose to use this becasue if we want to change any messages in the future it will be easy by only chaning what's isnide the vector and not all the code using the vector. This is used by loading a vector into a constructor and calling getRandomMessages to return a message.

The strings store characters like our messages,temp,weather etc. We chose to use this because it is the most simplest and effective way to pass around information.This is used by a lot of classes such as weather where it store the temp as a string.

Maps store key value pairs. We chose to use this because we don't want to write a lot of if-else statements and instead pair values. This is used by calling the key with the value pair to get the desired output.

Algorithms used:
The algorithms used were linear search, mapping,and time based polling.
Linear search is used in our saveData. It will like at our users in order and will add to list if it is not in there. The time Complexity here is O(n)
Mapping is used in our companion. It will take input value and compare it to defined thresholds and look until its found resulting in our desired face, outfit or clothing. The time complexitiy here is O(k) with k being the number of thresholds.
Time based pulling is used in our weather. It will use ana API to get the weather every so often. THe time complexiity here is O(1)

Development Reflection:
We encounter many problems such as using raylib. We did not have it downloaded and couldn't see our "fairy". We fixed this by using tutorials online to download it successfully 
One design improvement we made was using keys. We found it easier using keys instead of a list containing if else statements for our companion. Keys were a lot more readable, and simpler to implement out logic with.
For our V2 version we want to have the ability to bring this to a raspberry pi instead of console. Some of the features here were thought for a Pi but could also be used in the terminal too.
