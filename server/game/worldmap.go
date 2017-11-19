package game

type WorldMap struct {
	width  int32
	height int32
	tiles  []byte
}

func (wMap WorldMap) ToBytes() []byte {
	bytes := make([]byte, 0)

	// add width to stream
	bytes = append(bytes, Int32ToBytes(wMap.width)...)

	// add height to stream
	bytes = append(bytes, Int32ToBytes(wMap.height)...)

	bytes = append(bytes, wMap.tiles...)

	return bytes
}
