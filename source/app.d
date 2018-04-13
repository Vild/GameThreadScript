import std.stdio;
import std.string : toStringz;
import std.file : readText;

import lexer;

int main(string[] args) {
	foreach (arg; args[1 .. $]) {
		writeln("==== FILE ", arg, " ====");
		string data = arg.readText;
		Token t;
		do {
			t = getToken(data);
			t.write(" ");
		}
		while (!t.peek!EndOfFile);
		writeln("\n========");
		writeln();
	}

	return 0;
}
