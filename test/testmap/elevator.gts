package testmap;

class Elevator extends Entity;

@property Waypoint a;
@property Waypoint b;
@property float moveSpeed;

bool isAtA = true;

@override void init() {
	position = a;
}

@override void tick(float delta) {
	printf("Elevator tick: %f", delta);
}

@trigger void doMove() {
	Waypoint from = isAtA ? a : b;
	Waypoint to = isAtA ? b : a;

	float timeNeeded = (to - from).length / moveSpeed;
	auto endTime = Engine.time + timeNeeded;

	auto time = Engine.time;
	while (time < endTime) {
		position = lerp(to, from, (endTime - time) / timeNeeded);
		wait(1.tick);
	}
	position = to;
	isAtA = !isAtA;
}
