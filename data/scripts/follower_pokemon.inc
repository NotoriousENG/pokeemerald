Text_FollowerHappy::
	.string "{STR_VAR_1} looks happy\n"
	.string "to be walking with you.$"

EventScript_TalkToFollower::
	lock
	faceplayer
	specialvar VAR_0x8004, GetFollowerSpecies
	playmoncry VAR_0x8004, CRY_MODE_NORMAL
	waitmoncry
	bufferpartymonnick STR_VAR_1, 0
	message Text_FollowerHappy
	waitmessage
	waitbuttonpress
	release
	end
