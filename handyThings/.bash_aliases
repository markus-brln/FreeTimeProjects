# Markus own
alias ownit='sudo chown -R $USER ./' # own current dir recursively

# [Apt]
alias update='sudo apt update'  # updates your package list
alias upgrade='sudo apt upgrade -y'  # installs pending updates
alias dupgrade='sudo apt dist-upgrade -y'  # installs dist updates (kernel)
alias clean='sudo apt autoclean -y && sudo apt autoremove -y'  # cleans package list
alias install='sudo apt install -y'  # installs a new package
alias remove='sudo apt remove -y'  # removes a package
alias uudc='update && upgrade && dupgrade && clean'  # runs all updates and cleans afterwards 
alias search='apt-cache search'  # searches for a package

# [Git]
alias commit='git commit -m'  # does a git commit
alias push='git push'  # pushes current commits
alias add='git add . --all'  # adds all changed code
alias pull='git pull'  # pull all changes from remote
alias gitignore='git rm --cached `git ls-files -i -X .gitignore`'  # ignores files in gitignore

# [Misc]
alias cls='reset'  # clears your terminal (hard reset)
alias resetX='sudo restart lightdm'  # restarts the x server
alias pls='sudo !!'  # executes previous command as sudo
alias clear-thrash='rm -rf ~/.local/share/Trash/*'  # clears your thrash

# [Docker Compose]
alias dc='docker-compose'  # docker-compose shortcut
alias dcup='docker-compose up'  # ups service(s)
alias dcupd='docker-compose up -d'  # ups service(s) and detaches 
alias dcdown='docker-compose down'  # downs service(s)
alias dcx='docker-compose exec'  # run command in upped service
alias dcr='docker-compose run --rm'  # run command in new container (remove container after)
alias dcb='docker-compose build'  # builds service(s)
alias dcl='docker-compose log --follow'  # output and follow logs for service(s)

# [Ls]
alias la='ls -A'  # list all files (also hidden ones)
alias ll='ls -alh'  # list all information of all files (human readable)
