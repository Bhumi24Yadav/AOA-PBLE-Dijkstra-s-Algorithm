#include <stdio.h>

#define max 20
#define inf 99999

int graph[max][max];
int distance[max];
int visited[max];
int parent[max];

char locations[max][50] = {
    "Main Gate",
    "Library",
    "Computer Department",
    "Laboratory",
    "Auditorium"
};

int n = 5;
int graphEntered = 0;
int sourceSelected = 0;
int shortestPathFound = 0;
int source = -1;

void displayMenu()
{
    printf("\nCampus Locations:\n"
           "Main Gate\n"
           "Library\n"
           "Computer Department\n"
           "Laboratory\n"
           "Auditorium\n\n"
           "1. Enter Campus Graph\n"
           "2. Display Adjacency Matrix\n"
           "3. Select Source Location\n"
           "4. Find Shortest Distance\n"
           "5. Display Shortest Paths\n"
           "6. Display Distance from Source to All Locations\n"
           "7. Exit\n"
           "Enter your choice: ");
}

int findMinimumVertex()
{
    int minDistance;
    int minVertex;
    int i;

    minDistance = inf;
    minVertex = -1;

    for (i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < minDistance)
        {
            minDistance = distance[i];
            minVertex = i;
        }
    }

    return minVertex;
}

void enterGraph()
{
    int i;
    int j;
    int value;

    printf("\nEnter the distance between locations.\n");
    printf("Enter 0 if there is no direct connection.\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                printf("Distance from %s to %s: ",
                       locations[i], locations[j]);

                scanf("%d", &value);

                if (value == 0)
                {
                    graph[i][j] = inf;
                    graph[j][i] = inf;
                }
                else if (value > 0)
                {
                    graph[i][j] = value;
                    graph[j][i] = value;
                }
                else
                {
                    printf("Invalid distance.\n");
                    j--;
                }
            }
        }
    }

    graphEntered = 1;
    sourceSelected = 0;
    shortestPathFound = 0;
    source = -1;

    printf("\nCampus graph entered successfully!\n");
}

void displayMatrix()
{
    int i;
    int j;

    if (!graphEntered)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\nAdjacency Matrix:\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == inf)
                printf("inf\t");
            else
                printf("%d\t", graph[i][j]);
        }

        printf("\n");
    }
}

void selectSource()
{
    int i;
    int choice;

    if (!graphEntered)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\nCampus Locations:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, locations[i]);
    }

    printf("\nEnter source location number: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > n)
    {
        printf("Invalid location.\n");
        return;
    }

    source = choice - 1;
    sourceSelected = 1;
    shortestPathFound = 0;

    printf("Source selected: %s\n", locations[source]);
}

void dijkstra()
{
    int i;
    int count;
    int current;
    int v;

    for (i = 0; i < n; i++)
    {
        distance[i] = inf;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (count = 0; count < n - 1; count++)
    {
        current = findMinimumVertex();

        if (current == -1)
            break;

        visited[current] = 1;

        for (v = 0; v < n; v++)
        {
            if (!visited[v] &&
                graph[current][v] != inf &&
                distance[current] != inf &&
                distance[current] + graph[current][v] < distance[v])
            {
                distance[v] =
                    distance[current] + graph[current][v];

                parent[v] = current;
            }
        }
    }

    shortestPathFound = 1;
}

void findShortestDistance()
{
    int i;

    if (!graphEntered)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    if (!sourceSelected)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }

    dijkstra();

    printf("\nShortest Distances from %s:\n\n",
           locations[source]);

    printf("Destination : Distance\n");

    for (i = 0; i < n; i++)
    {
        if (distance[i] == inf)
            printf("%s : Unreachable\n", locations[i]);
        else
            printf("%s : %d\n", locations[i], distance[i]);
    }
}

void displayPath(int vertex)
{
    if (vertex == -1)
        return;

    if (vertex == source)
    {
        printf("%s", locations[vertex]);
        return;
    }

    displayPath(parent[vertex]);

    printf(" -> %s", locations[vertex]);
}

void displayShortestPaths()
{
    int i;

    if (!graphEntered)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    if (!sourceSelected)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }

    if (!shortestPathFound)
    {
        dijkstra();
    }

    printf("\nShortest Paths:\n\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        printf("Destination: %s\n", locations[i]);

        if (distance[i] == inf)
        {
            printf("Distance: Unreachable\n");
            printf("Path: No path available\n");
        }
        else
        {
            printf("Distance: %d\n", distance[i]);
            printf("Path: ");
            displayPath(i);
            printf("\n");
        }

        printf("\n");
    }
}

void displayDistances()
{
    int i;

    if (!graphEntered)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    if (!sourceSelected)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }

    if (!shortestPathFound)
    {
        printf("\nPlease find the shortest distance first using option 4.\n");
        return;
    }

    printf("\nDistance from %s to all locations:\n\n",
           locations[source]);

    printf("Destination : Distance\n");

    for (i = 0; i < n; i++)
    {
        if (distance[i] == inf)
            printf("%s : Unreachable\n", locations[i]);
        else
            printf("%s : %d\n", locations[i], distance[i]);
    }
}

int main()
{
    int choice;

    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                selectSource();
                break;

            case 4:
                findShortestDistance();
                break;

            case 5:
                displayShortestPaths();
                break;

            case 6:
                displayDistances();
                break;

            case 7:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid menu choice!\n");
        }

    } while (choice != 7);

    return 0;
}
