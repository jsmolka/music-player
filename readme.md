# egg-player
A Groove Music like music player.

## Features
A detailed description of all features will be added when the program is in a finished state.

- simple user interface
- reads audio tags
- background cover caching
- global shortcuts
- editable config
- error logs
- multiple library paths
- proper dpi scaling

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] [bass.dll](http://www.un4seen.com/) as audio backend
- [x] proper dpi scaling
- [ ] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Changes since lastest release
### New features
- UTF-8 support

### Changelog

## Things to do
### Internal
- load library in a separate thread
- add application startup to log
- add egg_old.log to store old logs
- char-by-char conversion instead of TStringToQString
- use namespaces or classes in utils

### Cosmetic
- [black title bar](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- fixed size for labels in SongInfo
- do not show certain info at low size
- library scroll acceleration
