# Room Sensor

Generic sensor board for collecting the following information about a room:
  - Temperature
  - Humidity
  - Ambient light level
  - Motion

## Flashing

E.g. for the living room:

```sh
esphome \
  -s room_id living-room \
  -s room_name "Living Room" \
  run room-sensor.yaml
```
