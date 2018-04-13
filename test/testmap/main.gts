package testmap;

class TestMap : Map;

@property Elevator theElevator;

@override void init() {
	startThread(moveTheElevator);

	string derp = "WeebFreak";
	ulong derp2 = 1337;
	double derp3 = 0.3;

	char testchar;
	byte testbyte;
	short testshort;
	int testint;
	long testlong;
	ubyte testubyte;
	ushort testushort;
	uint testuint;
	float testfloat;

	foreach (e; world.getEntities<Elevator>())
		if (e != theElevator)
			startThread(moveElevator, e);
}

void moveTheElevator() {
	while (true) {
		wait(4.second);
		theElevator.doMove();
	}
}

void moveElevator(Elevator self) {
	while (true) {
		wait(4.second);
		self.doMove();
	}
}
