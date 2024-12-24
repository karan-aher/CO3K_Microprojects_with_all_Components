#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 5          // Total number of rooms available
#define MAX_NAME_LENGTH 50
#define AC_ROOM_RENT 1500    // Rent for AC room
#define NON_AC_ROOM_RENT 1000 // Rent for Non-AC room

// Structure to store customer information
struct Customer {
    char name[MAX_NAME_LENGTH];
    int roomNumber;
    int daysStayed;
    int isOccupied;         // 1 if room is occupied, 0 if not
    char roomType[10];      // Type of room: AC or Non-AC
};

// Function to save room data to a file
void saveToFile(struct Customer hotel[]) {
    FILE *file = fopen("hotel_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < MAX_ROOMS; i++) {
        fprintf(file, "Room %d (%s): ", hotel[i].roomNumber, hotel[i].roomType);
        if (hotel[i].isOccupied) {
            fprintf(file, "Occupied by %s for %d days\n", hotel[i].name, hotel[i].daysStayed);
        } else {
            fprintf(file, "Available\n");
        }
    }

    fclose(file);
}

// Initialize hotel with empty rooms
void initializeRooms(struct Customer hotel[]) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        hotel[i].roomNumber = i + 1;
        hotel[i].isOccupied = 0;  // All rooms are initially available
        // Set room type based on room number
        if (i < MAX_ROOMS / 2) {
            strcpy(hotel[i].roomType, "AC Room"); // First half are AC Rooms
        } else {
            strcpy(hotel[i].roomType, "Non-AC Room"); // Second half are Non-AC Rooms
        }
    }

    // Save initial room data to file
    saveToFile(hotel);
}

// Function to display all rooms and their status
void displayRooms(struct Customer hotel[]) {
    printf("\n--- Room Status ---\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (hotel[i].isOccupied) {
            printf("Room %d (%s): Occupied by %s\n", hotel[i].roomNumber, hotel[i].roomType, hotel[i].name);
        } else {
            printf("Room %d (%s): Available\n", hotel[i].roomNumber, hotel[i].roomType);
        }
    }
}

// Function to book a room
void bookRoom(struct Customer hotel[]) {
    int roomNumber, days;
    char name[MAX_NAME_LENGTH];

    printf("\nEnter Room Number to Book (1-%d): ", MAX_ROOMS);
    scanf("%d", &roomNumber);

    // Check if room is available
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }

    if (hotel[roomNumber - 1].isOccupied) {
        printf("Sorry, Room %d is already occupied.\n", roomNumber);
        return;
    }

    // Booking process
    printf("Enter Your Name: ");
    scanf("%s", name);
    printf("Enter Number of Days of Stay: ");
    scanf("%d", &days);

    // Assign room to the customer
    strcpy(hotel[roomNumber - 1].name, name);
    hotel[roomNumber - 1].daysStayed = days;
    hotel[roomNumber - 1].isOccupied = 1;

    printf("Room %d (%s) booked successfully for %s for %d days!\n", roomNumber, hotel[roomNumber - 1].roomType, name, days);

    // Save updated room data to file
    saveToFile(hotel);
}

// Function to checkout and calculate bill
void checkout(struct Customer hotel[]) {
    int roomNumber;
    int totalBill;

    printf("\nEnter Room Number to Checkout: ");
    scanf("%d", &roomNumber);

    // Check if the room is valid and occupied
    if (roomNumber < 1 || roomNumber > MAX_ROOMS || !hotel[roomNumber - 1].isOccupied) {
        printf("Invalid room number or the room is not occupied.\n");
        return;
    }

    // Calculate total bill based on room type
    if (strcmp(hotel[roomNumber - 1].roomType, "AC Room") == 0) {
        totalBill = hotel[roomNumber - 1].daysStayed * AC_ROOM_RENT;
    } else {
        totalBill = hotel[roomNumber - 1].daysStayed * NON_AC_ROOM_RENT;
    }

    printf("Checkout successful for %s. Total Bill: INR %d\n", hotel[roomNumber - 1].name, totalBill);

    // Free up the room
    hotel[roomNumber - 1].isOccupied = 0;

    // Save updated room data to file
    saveToFile(hotel);
}

// Function to unbook a room
void unbookRoom(struct Customer hotel[]) {
    int roomNumber;

    printf("\nEnter Room Number to Unbook: ");
    scanf("%d", &roomNumber);

    // Check if the room is valid and occupied
    if (roomNumber < 1 || roomNumber > MAX_ROOMS || !hotel[roomNumber - 1].isOccupied) {
        printf("Invalid room number or the room is not occupied.\n");
        return;
    }

    // Free up the room
    hotel[roomNumber - 1].isOccupied = 0;
    printf("Room %d (%s) unbooked successfully!\n", roomNumber, hotel[roomNumber - 1].roomType);

    // Save updated room data to file
    saveToFile(hotel);
}

int main() {
    struct Customer hotel[MAX_ROOMS];
    int choice;

    // Initialize rooms
    initializeRooms(hotel);

    while (1) {
        printf("\n--- Hotel Management System ---\n");
        printf("1. Display Room Status\n");
        printf("2. Book a Room\n");
        printf("3. Checkout and Generate Bill\n");
        printf("4. Unbook a Room\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayRooms(hotel);
                break;
            case 2:
                bookRoom(hotel);
                break;
            case 3:
                checkout(hotel);
                break;
            case 4:
                unbookRoom(hotel);
                break;
            case 5:
                printf("Exiting Hotel Management System...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
