export PS1='\W$ '
export LANG=en_US.UTF-8

alias ll='ls -l'
alias la='ls -la'
alias h='history |sed "/ \+[0-9]\+ \+h$/d"'

if [ -f ~/.bashrc ]; then . ~/.bashrc; fi
