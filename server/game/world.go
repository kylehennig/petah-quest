package game

const(
	COLOUR_BLK byte = iota
	COLOUR_RED
	COLOUR_GRN
	COLOUR_YLW
	COLOUR_BLU
	COLOUR_MAG
	COLOUR_CYN
	COLOUR_WHT
)

type WorldMap struct {
	width int
	height int
	tiles []byte
}

func GetAvailableID() int{
	return 1
}

func NewPlayer(ch byte) Entity {
	playerType := Type{COLOUR_WHT, ch,fist() ,5}
	return Entity{GetAvailableID(),0,0, 100, playerType}
}

func (wMap WorldMap) ToBytes() []byte {
	bytes := make([]byte, 0)

	// add width to stream
	bytes = append(bytes, intToBytes(wMap.width)...)

	// add height to stream
	bytes = append(bytes, intToBytes(wMap.height)...)

	bytes = append(bytes, wMap.tiles...)

	return bytes
}

func GetMap() WorldMap{
	return loadMap()
}
func intToBytes(n int) []byte {
	bytes := make([]byte, 4)
	bytes[0] = (byte) ((n >> 24) & 0xFF)
	bytes[1] = (byte) ((n >> 16) & 0xFF)
	bytes[2] = (byte) ((n >> 8) & 0xFF)
	bytes[3] = (byte) (n & 0xFF)
	return bytes
}