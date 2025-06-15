#pragma once

struct Player {
	float speed{ 200.0f };
	float jumpForce{ 400.0f };
	bool isGrounded{ true };
	bool canJump{ true };
};