# Music Player

🎶 **Music Player** is a command-line based application built in C, designed to manage and play music files with ease. This lightweight music player includes functionalities like adding and removing music, navigating through tracks, and user management through registration and login. It uses a doubly linked list for efficient track management.

## Features

- **User Management**: Register, login, and manage user accounts.
- **Music Management**: Add, remove, and view your playlist.
- **Track Navigation**: Play the first, last, next, previous, or a specific track from your playlist.
- **Pause Music**: Pause any currently playing track.
- **Persistent Storage**: Save and restore playlists for each user.

## Getting Started

### Prerequisites

- Ensure you have a C compiler installed (e.g., GCC).
- Works on Windows due to the use of `system("cls")` and `-lwinmm`.

### Installation

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/YOUR_GITHUB_USERNAME/music-player.git
cd music-player
```

Compile the source code using the following command:

```bash
gcc music_player.c -o music_player -lwinmm
```

### Usage

Run the program:

```bash
./music_player
```

Upon starting the application, you will be greeted with the main menu. You can choose to:

1. **Register**: Create a new user account.
2. **Login**: Access your existing account.
3. **Show Users**: Display all registered users.
4. **Exit**: Quit the application.

After logging in, you will have access to the user panel with the following options:

1. **Add Music**: Add new music files to your playlist.
2. **Remove Music**: Remove music files from your playlist.
3. **Show Playlist**: View the current playlist.
4. **Play Next File**: Play the next track in the playlist.
5. **Play Previous File**: Play the previous track.
6. **Play First File**: Start with the first track in the playlist.
7. **Play Last File**: Play the last track in the playlist.
8. **Play Specific File**: Choose a specific track to play.
9. **Exit**: Exit the user panel.
0. **Pause Any Music**: Pause the currently playing track.

### Key Commands
- Use numerical inputs to select options from the menu.
- Follow on-screen instructions for each feature.

## Contributing
Contributions are welcome! If you have suggestions for improvements or want to add new features, feel free to fork the repository and submit a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for more details.

## Author
Yash Kayastha
If you need any other modifications or have additional requirements, feel free to ask!
