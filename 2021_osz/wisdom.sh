#!/bin/sh

case $1 in
1)
	printf '"There are only two kinds of languages: the ones people complain about and the ones nobody uses" -- Bjarne Stroustrup' | cowsay -f stegosaurus.cow;;
2)
	printf '"Code can be so complex that there are no obvious bugs or so simple that there are obviously no bugs"' | cowsay -f turtle.cow;;
3)
	printf '"Controlling complexity is the essence of computer programming." -- Brian Kernigan' | cowsay -f dragon.cow;;
4)
	printf '"Any fool can write code that a computer can understand. Good programmers write code that humans can understand." -- Martin Fowler' | cowsay -f elephant.cow;;
5)
	printf '"C makes it easy to shoot yourself in the foot. C++ makes it harder, but when you do, you blow away your whole leg!" -- Bjarne Stroustrup' | cowsay -f moose.cow;;
6)
	printf '"The first 90 percent of the code accounts for the first 90 percent of the development time. The remaining 10 percent of the code account for the other 90 percent of the development time." -- Tom Cargill' | cowsay -f turkey.cow;;
7)
	printf '"Always code as if the guy who ends up maintaining your code will be a violent psychopath who knows where you live." -- Martin Golding' | cowsay -f bud-frogs.cow;;
8)
	printf "\"C++ is designed to allow you to express ideas, but if you don't have ideas or don't have any clue about how to express them, C++ doesn't offer much help.\" -- Bjarne Stroustrup" | cowsay -f kitty.cow;;
9)
	printf "\"Write shy code - modules that don't reveal anything unnecessary to other modules and that don't rely on other modules' implementations.\" -- Andy Hunt" | cowsay -f blowfish.cow;;
10)
	printf "Próbáljátok ki:\n\ncodingame.com/multiplayer/clashofcode" | cowsay -f tux.cow;;
11)
	printf "https://code.golf/" | cowsay -f tux.cow;;
12)
	printf "\"The fact is, there aren't just two sides to any issue, there's almost always a range of responses, and \"it depends\" is almost always the right answer in any big question.\" -- Linus Torvalds" | cowsay -f tux.cow;;
13)
	tput setaf 214 # orange
	printf "Ha már unjátok a C++-t:\n\nhttps://esolangs.org/wiki/Language_list" | cowsay -f doge.cow;;
all)
	for i in $(seq 13); do
		$0 "$i"
		echo
	done;;
"")
	printf 'Óra nem lett megadva!\n' >&2
	exit 1;;
*)
	printf 'Ilyen óra nincs vagy nincs hozzá bölcsesség!\n' >&2
	exit 2;;
esac
