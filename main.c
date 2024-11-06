#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a player (node)
typedef struct Player {
    char name[50];
    int score;
    struct Player* left;
    struct Player* right;
} Player;

// Function to create a new player node
Player* createPlayer(char* name, int score) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(newPlayer->name, name);
    newPlayer->score = score;
    newPlayer->left = newPlayer->right = NULL;
    return newPlayer;
}

// Function to insert a new player into the BST
Player* insertPlayer(Player* root, char* name, int score) {
    if (root == NULL) {
        return createPlayer(name, score);
    }

    // Insert based on score (higher score goes to the right, lower goes to the left)
    if (score > root->score) {
        root->right = insertPlayer(root->right, name, score);
    } else if (score < root->score) {
        root->left = insertPlayer(root->left, name, score);
    } else {
        // If scores are equal, insert based on name alphabetically
        if (strcmp(name, root->name) < 0) {
            root->left = insertPlayer(root->left, name, score);
        } else {
            root->right = insertPlayer(root->right, name, score);
        }
    }
    return root;
}

// Function to delete a player from the BST (based on name)
Player* deletePlayer(Player* root, char* name) {
    if (root == NULL) {
        return NULL;
    }

    // Search for the player to delete
    if (strcmp(name, root->name) < 0) {
        root->left = deletePlayer(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = deletePlayer(root->right, name);
    } else {
        // Node to be deleted is found
        if (root->left == NULL) {
            Player* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Player* temp = root->left;
            free(root);
            return temp;
        }

        // If the node has two children, find the inorder successor (smallest in the right subtree)
        Player* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        strcpy(root->name, temp->name);
        root->score = temp->score;

        // Delete the inorder successor
        root->right = deletePlayer(root->right, temp->name);
    }
    return root;
}

// Function to perform a reverse in-order traversal to print the leaderboard (descending order)
void printLeaderboard(Player* root) {
    if (root == NULL) {
        return;
    }

    // Visit the right subtree first (higher scores)
    printLeaderboard(root->right);
    
    // Print the current node
    printf("%s: %d\n", root->name, root->score);
    
    // Visit the left subtree (lower scores)
    printLeaderboard(root->left);
}

// Function to search for a player by name
Player* searchPlayer(Player* root, char* name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return searchPlayer(root->left, name);
    }

    return searchPlayer(root->right, name);
}

int main() {
    Player* root = NULL;
    int choice;
    char name[50];
    int score;

    while (1) {
        printf("\nGame Leaderboard System\n");
        printf("1. Add Player\n");
        printf("2. Delete Player\n");
        printf("3. View Leaderboard\n");
        printf("4. Search Player\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline after scanf

        switch (choice) {
            case 1:
                printf("Enter player's name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character from fgets
                printf("Enter player's score: ");
                scanf("%d", &score);
                root = insertPlayer(root, name, score);
                break;

            case 2:
                printf("Enter the name of the player to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character from fgets
                root = deletePlayer(root, name);
                break;

            case 3:
                printf("\nLeaderboard (Highest Score First):\n");
                printLeaderboard(root);
                break;

            case 4:
                printf("Enter player's name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character from fgets
                Player* found = searchPlayer(root, name);
                if (found != NULL) {
                    printf("Player found: %s with score %d\n", found->name, found->score);
                } else {
                    printf("Player not found!\n");
                }
                break;

            case 5:
                printf("Exiting the system...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
