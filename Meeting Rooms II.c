class Solution {
  public:
    int minMeetingRooms(vector<int> &start, vector<int> &end) {

        // Sort both start and end times
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int n = start.size();
        int rooms = 0;
        int maxRooms = 0;
        int l = 0, r = 0;

        // Use two pointers technique to traverse start and end arrays
        while (l < n && r < n) {

            // If the meeting starts before the earliest ending one, a new room is
            // needed
            if (start[l] < end[r]) {
                ++rooms;
                ++l;
            }

            // Else, one meeting ends, free a room
            else {
                --rooms;
                ++r;
            }

            // Track the maximum number of rooms needed at any point in time
            maxRooms = max(maxRooms, rooms);
        }

        return maxRooms;
    }
};
