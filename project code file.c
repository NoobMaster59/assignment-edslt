#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 6
#define SIZE 20
#define POWER_LOG_SIZE 5

// ------------------------
// Task A: Queue + Stack (Interactive)
// ------------------------

char queue[MAX][SIZE];
int front = -1, rear = -1;

char stack[MAX][SIZE];
int top = -1;

void enqueue(char* request) {
    if (rear == MAX - 1) {
        printf("Queue is full. Cannot enqueue %s\n", request);
        return;
    }
    if (front == -1) front = 0;
    rear++;
    strcpy(queue[rear], request);
    printf("%s enqueued.\n", request);
}

char* dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }
    char* item = queue[front++];
    printf("%s dequeued.\n", item);
    return item;
}

void push(char* request) {
    if (top == MAX - 1) {
        printf("Stack is full. Cannot push %s\n", request);
        return;
    }
    top++;
    strcpy(stack[top], request);
    printf("%s pushed onto stack.\n", request);
}

char* pop() {
    if (top == -1) {
        printf("Stack is empty. Cannot pop.\n");
        return NULL;
    }
    char* item = stack[top--];
    printf("%s popped from stack.\n", item);
    return item;
}

void task_a_flow_emergency_interactive() {
    printf("\n--- Task A: Flow and Emergency (Interactive) ---\n");

    int choice;
    char request[SIZE];

    do {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue a request\n");
        printf("2. Dequeue a request\n");
        printf("\nStack Operations (Emergency):\n");
        printf("3. Push to emergency stack\n");
        printf("4. Pop from emergency stack\n");
        printf("5. Exit Task A\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter request to enqueue: ");
                fgets(request, SIZE, stdin);
                request[strcspn(request, "\n")] = 0; // Remove trailing newline
                enqueue(request);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                printf("Enter request to push to stack: ");
                fgets(request, SIZE, stdin);
                request[strcspn(request, "\n")] = 0;
                push(request);
                break;
            case 4:
                pop();
                break;
            case 5:
                printf("Exiting Task A.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

// ------------------------
// Task B: Power Log (Interactive)
// ------------------------

char power_log[POWER_LOG_SIZE][SIZE];
int log_index = 0;
int log_count = 0;

void log_power(char* output) {
    if (log_count < POWER_LOG_SIZE) {
        strcpy(power_log[log_index++], output);
        log_count++;
        printf("%s logged.\n", output);
    } else {
        printf("Transmitting (Oldest): %s\n", power_log[0]);
        for (int i = 1; i < POWER_LOG_SIZE; i++) {
            strcpy(power_log[i - 1], power_log[i]);
        }
        strcpy(power_log[POWER_LOG_SIZE - 1], output);
        printf("%s logged (oldest overwritten).\n", output);
    }
}

void display_power_log() {
    printf("\nCurrent Power Log:\n");
    for (int i = 0; i < log_count; i++) {
        printf("%s\n", power_log[i]);
    }
}

void task_b_power_log_interactive() {
    printf("\n--- Task B: Power Output Log (Interactive) ---\n");

    int choice;
    char output[SIZE];

    do {
        printf("\nPower Log Operations:\n");
        printf("1. Log a power output\n");
        printf("2. Display current log\n");
        printf("3. Exit Task B\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter power output to log: ");
                fgets(output, SIZE, stdin);
                output[strcspn(output, "\n")] = 0;
                log_power(output);
                break;
            case 2:
                display_power_log();
                break;
            case 3:
                printf("Exiting Task B.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// ------------------------
// Task C: Maintenance Tracker (Interactive)
// Singly + Doubly Linked List
// ------------------------

typedef struct SNode {
    char name[SIZE];
    struct SNode* next;
} SNode;

typedef struct DNode {
    char name[SIZE];
    struct DNode* prev;
    struct DNode* next;
} DNode;

SNode* worn_head = NULL;
DNode* repaired_head = NULL;

void insert_worn(char* name) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, name);
    newNode->next = worn_head;
    worn_head = newNode;
    printf("%s added to worn components.\n", name);
}

void delete_worn(char* name) {
    SNode *temp = worn_head, *prev = NULL;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("%s not found in worn components.\n", name);
        return;
    }

    if (prev == NULL)
        worn_head = temp->next;
    else
        prev->next = temp->next;

    printf("%s removed from worn components.\n", temp->name);
    free(temp);
}

void insert_repaired(char* name) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, name);
    newNode->prev = NULL;
    newNode->next = repaired_head;

    if (repaired_head != NULL)
        repaired_head->prev = newNode;

    repaired_head = newNode;
    printf("%s added to repaired components.\n", name);
}

void traverse_repaired_forward() {
    DNode* temp = repaired_head;
    printf("\nRepaired Components (Forward):\n");
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

void traverse_repaired_backward() {
    DNode* temp = repaired_head;
    if (temp == NULL) {
        printf("Repaired components list is empty.\n");
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("\nRepaired Components (Backward):\n");
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->prev;
    }
}

void display_worn_components() {
    SNode* temp = worn_head;
    printf("\nWorn Components:\n");
    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

void task_c_worn_tracker_interactive() {
    printf("\n--- Task C: Worn Component Tracker (Interactive) ---\n");

    int choice;
    char component_name[SIZE];

    do {
        printf("\nWorn Components Operations:\n");
        printf("1. Add a worn component\n");
        printf("2. Remove a worn component\n");
        printf("3. Display worn components\n");
        printf("\nRepaired Components Operations:\n");
        printf("4. Add a repaired component\n");
        printf("5. Display repaired components (Forward)\n");
        printf("6. Display repaired components (Backward)\n");
        printf("7. Exit Task C\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter name of worn component to add: ");
                fgets(component_name, SIZE, stdin);
                component_name[strcspn(component_name, "\n")] = 0;
                insert_worn(component_name);
                break;
            case 2:
                printf("Enter name of worn component to remove: ");
                fgets(component_name, SIZE, stdin);
                component_name[strcspn(component_name, "\n")] = 0;
                delete_worn(component_name);
                break;
            case 3:
                display_worn_components();
                break;
            case 4:
                printf("Enter name of repaired component to add: ");
                fgets(component_name, SIZE, stdin);
                component_name[strcspn(component_name, "\n")] = 0;
                insert_repaired(component_name);
                break;
            case 5:
                traverse_repaired_forward();
                break;
            case 6:
                traverse_repaired_backward();
                break;
            case 7:
                printf("Exiting Task C.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

// ------------------------
// Task D: Priority Tuning (Interactive)
// Circular Linked List
// ------------------------

typedef struct CNode {
    char name[SIZE];
    struct CNode* next;
} CNode;

CNode* circular_head = NULL;

void insert_circular(char* name) {
    CNode* newNode = (CNode*)malloc(sizeof(CNode));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, name);

    if (circular_head == NULL) {
        circular_head = newNode;
        newNode->next = circular_head;
    } else {
        CNode* temp = circular_head;
        while (temp->next != circular_head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = circular_head;
    }
    printf("%s added to priority tuning.\n", name);
}

void traverse_circular(int rounds) {
    if (!circular_head) {
        printf("Priority tuning list is empty.\n");
        return;
    }

    CNode* temp = circular_head;
    printf("\nCircular Priority Tuning (%d rounds):\n", rounds);
    for (int i = 0; i < rounds * 2; i++) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

void task_d_priority_tuning_interactive() {
    printf("\n--- Task D: Priority Tuning (Interactive) ---\n");

    int choice, rounds;
    char component_name[SIZE];

    do {
        printf("\nPriority Tuning Operations:\n");
        printf("1. Add a component for tuning\n");
        printf("2. Traverse the tuning cycle\n");
        printf("3. Exit Task D\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter name of component to add for tuning: ");
                fgets(component_name, SIZE, stdin);
                component_name[strcspn(component_name, "\n")] = 0;
                insert_circular(component_name);
                break;
            case 2:
                printf("Enter the number of rounds to traverse: ");
                scanf("%d", &rounds);
                getchar(); // Consume the newline character
                traverse_circular(rounds);
                break;
            case 3:
                printf("Exiting Task D.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// ------------------------
// Main Program Starts Here (Interactive Menu)
// ------------------------

int main() {
    int main_choice;

    do {
        printf("\n--- Hydroelectric Power Plant Simulation Menu ---\n");
        printf("1. Task A: Flow and Emergency Management\n");
        printf("2. Task B: Power Output Log\n");
        printf("3. Task C: Worn Component Tracker\n");
        printf("4. Task D: Priority Tuning\n");
        printf("5. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &main_choice);
        getchar(); // Consume the newline character

        switch (main_choice) {
            case 1:
                task_a_flow_emergency_interactive();
                break;
            case 2:
                task_b_power_log_interactive();
                break;
            case 3:
                task_c_worn_tracker_interactive();
                break;
            case 4:
                task_d_priority_tuning_interactive();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (main_choice != 5);

    // Free allocated memory (important for linked lists)
    SNode* current_worn = worn_head;
    while (current_worn != NULL) {
        SNode* next_worn = current_worn->next;
        free(current_worn);
        current_worn = next_worn;
    }

    DNode* current_repaired = repaired_head;
    while (current_repaired != NULL) {
        DNode* next_repaired = current_repaired->next;
        free(current_repaired);
        current_repaired = next_repaired;
    }

    CNode* current_circular = circular_head;
    if (current_circular != NULL) {
        CNode* temp = current_circular->next;
        while (temp != current_circular) {
            CNode* next_circular = temp->next;
            free(temp);
            temp = next_circular;
        }
        free(current_circular);
    }

    return 0;
}
