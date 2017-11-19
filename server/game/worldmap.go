package game


type WorldMap struct {
	width int
	height int
	tiles []byte
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
	bytes[3] = (byte) ((n >> 24) & 0xFF)
	bytes[2] = (byte) ((n >> 16) & 0xFF)
	bytes[1] = (byte) ((n >> 8) & 0xFF)
	bytes[0] = (byte) (n & 0xFF)
	return bytes
}
