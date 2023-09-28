#include <string>

class TransitionTile {
  public:
    int x, y;
    std::string destinationRoomId;

    TransitionTile(
        int x,
        int y,
        const std::string& destinationRoomId
        ) : x(x), y(y), destinationRoomId(destinationRoomId) {}

    // You can add more methods and properties if needed
};
