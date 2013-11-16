Build Instructions

cd libs
Extract the appropriate poco lib (i.e. .tar.gz for *nix, .zip for windows)
cd into the extracted directory
Run: ./configure --prefix=`pwd` --no-samples --no-tests; make; make install
Return to the root MyRepo directory
Run: make; make install

To make the client (recommended to do this last):
cd Client
make

Movies DB:
There exists movie DB query functionality (although primitive and clunky). To retrieve the text database to import, visit:
ftp://ftp.fu-berlin.de/pub/misc/movies/database/movies.list.gz

Instructions:
Connect servers one at a time. After the "0" server has received its id (i.e. the most recently connected), you can start
a new server safely to join the network.

Client Commands:
insert <key> <value>
lookup <key>
remove <key>

importmovielist <movie_list.txt>
movielup <key_word>

Additional notes:
movielup will return a list of all movies with the keyword. Due to time, this is done in a naive way (which is the reason for the
  note to follow). A better implementation would have been to simply use mapreduce.

To import a movie list, first connect to a single server and import the list. After the list is imported, you can begin joining
other servers. Please note that when joining other servers, the entire database must be replicated (and the "0" id must be received)
before it is safe to join another server.


