#include <stdlib.h>
#include <stdio.h>
#include <linkedlist.h>
#include <string.h>
#include <hashmap.h>
#include <time.h>

typedef struct TERRITORY
{
  int id;
  char * name;
  char * occupiedBy;
  int occupiedById;
  int numberOfDefendingTroops;
  char * attackedBy;
  int numberOfAttackingTroops;
  Node * adjoiningTerritories;
} Territory;

void initializeTerritory(Territory * t, int id, char * name)
{

  t->id = id;
  t->name = name;
  t->occupiedBy = NULL;
  t->occupiedById = 0;
  t->numberOfDefendingTroops = 0;
  t->attackedBy = NULL;
  t->numberOfAttackingTroops = 0;
  t->adjoiningTerritories = NULL;
}

typedef struct PLAYER
{
  char * name;
  int id;
  Node * occupiedTerritories;
  int numberOfUndeployedTroops;
} Player;

void printCharLine(char c, int count)
{
  int i = 0;
  for (i = 0; i < count; i++)
  {
    printf("%c", c);
  }
  printf("\n");
}

void printChar(char c, int count)
{
  int i = 0;
  for (i = 0; i < count; i++)
  {
    printf("%c", c);
  }
}


void initializePlayer(Player * player, char * name)
{
  player->name = name;
  player->id = 0;
  player->occupiedTerritories = NULL;
  player->numberOfUndeployedTroops = 20;
}

int unoccupiedTerritoryCount(Node * territoryList)
{ 
  int count = 0;
  Node * p = territoryList;
  while (p != NULL)
  {
    Territory * t = (Territory *)p->data;
    if (t->occupiedBy == NULL)
    {
      count++;
    }
    p = p->next;
  }

  return count;
}
int terId = 0;
Territory * selectUnoccupiedTerritory(Node * territoryList, Player * player)
{
    Node * p = territoryList;
    int lineLength = 0;
    while (p != NULL)
    {
       Territory * t = (Territory *)p->data;
       if (t->occupiedBy == NULL)
       {
         if (t->id < 10)
         {
           printf("%d   %s", t->id, t->name);
         }
         else
         {
           printf("%d  %s", t->id, t->name);
         }
         int nameLength = strlen(t->name);
         while (nameLength < 30)
         {
           printf(" ");
           nameLength += 1;
         }
         lineLength = lineLength + nameLength;
         lineLength += 3;
         if (lineLength > 100)
         {
           lineLength = 0;
           printf("\n");
         }   
       }
       p = p->next;   
    }

  printf("\n\nPlayer %s select a territory.\n", player->name);

  char buffer[100];
//  scanf ("%[^\n]%*c", buffer);

  int id = terId++;//atoi(buffer);
  while (id < 0 || id > 41)
  {
    printf("Enter the number of one of the available territories.\n");
    scanf ("%[^\n]%*c", buffer);
    id = atoi(buffer);
  }
  if (id > -1 && id < 42)
  {
    Node * p = territoryList;
    while (p != NULL)
    {
      Territory * t = (Territory *)p->data;
      if (t->id == id)
      {
        if (t->occupiedBy == NULL)
        {
          t->occupiedBy = player->name;
          t->occupiedById = player->id;
          t->numberOfDefendingTroops = 1;
          if (player->occupiedTerritories == NULL)
          {
            player->occupiedTerritories = linkedListCreate(t);
          }
          else
          {
            linkedListAdd(player->occupiedTerritories, t);
          }
          break;
        } 
        else
        {
          printf("%s is already occupied. Select another territory.\n", t->name);
          id = -1;
          while (id < 0 || id > 41)
          {
            scanf ("%[^\n]%*c", buffer);
            id = atoi(buffer);
          }
        }
      }
      p = p->next;
    }
  } 
    
    return NULL;
}

void turn(Node * territoryList, Player * player, Node * playerList)
{
    char buffer[100];
    int capturedTerritory = 0;
    int attack = 1;
    while (attack > 0)
    {
      printCharLine('_', 140);
      Node * p = player->occupiedTerritories;
      int lineLength = 0;
      int territoriesToAttackFromCount = 0;
    while (p != NULL)
    {
       Territory * t = (Territory *)p->data;
       if (t->numberOfDefendingTroops > 1)
       {
           territoriesToAttackFromCount++;
           printf("(%2d)   %s with %2d troops", t->id, t->name, t->numberOfDefendingTroops);

       int nameLength = strlen(t->name);
       printChar(' ', 30 - nameLength);
       if (nameLength < 30)
       {
         nameLength += 30 - nameLength;
       }

       lineLength = lineLength + nameLength;
       lineLength += 3;
       if (lineLength > 70)
       {
         lineLength = 0;
         printf("\n");
       }
      }   
       p = p->next;   
    }

  if (territoriesToAttackFromCount > 0) 
  {
    printf("\n\nPlayer %s you occupy these territories with enough troops to launch an attack.\n", player->name);
    printf("Player %s select a territory to launch an invasion from.\n", player->name);
  }
  else
  {
    break;
  }

  scanf ("%[^\n]%*c", buffer);
  int id = atoi(buffer);
  Territory * selectedTerritory = NULL;
  while (id < 0 || id > 41 || selectedTerritory == NULL)
  {
      Node * p = player->occupiedTerritories;
      while (p != NULL)
      {
        Territory * t = (Territory *)p->data;
        if (t->id == id)
        {
          selectedTerritory = t;
          break;
        }
        p = p->next;
      } 
    if (selectedTerritory == NULL)
    {
      printf("Enter the number of one of your available territories.\n");
      scanf ("%[^\n]%*c", buffer);
      id = atoi(buffer);
    } 
    else
    {
      break;
    }
  }
   printf("Player %s has selected %s to attack from.\n", player->name, selectedTerritory->name);
   p = selectedTerritory->adjoiningTerritories;
   lineLength = 0;
    while (p != NULL)
    {
       Territory * t = (Territory *)p->data;
       int ownTerritory = 0; 
       Node * pp = player->occupiedTerritories;
       while (pp != NULL)
       {
         Territory * tt = (Territory *)pp->data;
         if (tt->id == t->id)
         {
           ownTerritory = 1;
           break;
         }
         pp = pp->next;
       }

       if (!ownTerritory > 0)
       {
         printf("(%2d)   %s defended by %2d  troops", t->id, t->name, t->numberOfDefendingTroops);
          
         int nameLength = strlen(t->name);
         printChar(' ', 30 - nameLength);
         if (nameLength < 30)
         {
           nameLength += 30 - nameLength;
         }
        
         lineLength = lineLength + nameLength;
         lineLength += 3;
         if (lineLength > 70)
         {
           lineLength = 0;
           printf("\n");
         }
       }   
       p = p->next;   
    }


  printf("\n\n\nPlayer %s select a territory to invade.\n", player->name);

  scanf ("%[^\n]%*c", buffer);
  id = atoi(buffer);
  Territory * selectedTerritoryToInvade = NULL;
  Node * selectedNodeToInvade = NULL;
  while (id < 0 || id > 41 || selectedTerritoryToInvade == NULL)
  {
    if (id > -1 && id < 42)
    {
      Node * p = selectedTerritory->adjoiningTerritories;
    
      while (p != NULL)
      {
        Territory * t = (Territory *)p->data;
        if (t->id == id)
        {
          selectedTerritoryToInvade = t;
          selectedNodeToInvade = p;
          break;
        }
        p = p->next;
      }
    } 
    if (selectedTerritoryToInvade == NULL)
    {
      id = -1;
    } 
    else
    {
      break;
    }
  }

  printCharLine('_', 140);
  printf("Player %s is invading %s\n", player->name, selectedTerritoryToInvade->name);
  printf("Enter the number of troops to invade. (from 1 to %d)\n", selectedTerritory->numberOfDefendingTroops - 1);
  scanf ("%[^\n]%*c", buffer);
  int numberOfInvadingTroops = atoi(buffer);
  while (numberOfInvadingTroops < 0 || numberOfInvadingTroops > selectedTerritory->numberOfDefendingTroops - 1)
  {
    printf("Enter the number of troops to invade. (from 1 to %d)\n", selectedTerritory->numberOfDefendingTroops - 1);
    scanf ("%[^\n]%*c", buffer);
    numberOfInvadingTroops = atoi(buffer);
  }
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  int d1 = 0;
  int d2 = 0;
  a1 = rand() % 6 + 1;
  if (numberOfInvadingTroops > 1)
  {   
    a2 = rand() % 6 + 1;
  }
  if (numberOfInvadingTroops > 2)
  {
    a3 = rand() % 6 + 1;
  }

  d1 = rand() % 6 + 1;
  if (selectedTerritoryToInvade->numberOfDefendingTroops > 1)
  {
    d2 = rand() % 6 + 1;
  }

  if (a1 < a2)
  {
    int temp = a1;
    a1 = a2;
    a2 = temp;
  }
  if (a1 < a3)
  {
    int temp = a1;
    a1 = a3;
    a3 = temp;
  }

  if (a2 < a3)
  {
    int temp = a2;
    a2 = a3;
    a3 = temp;
  }
  
  if (d1 < d2)
  {
    int temp = d1;
    d1 = d2;
    d2 = temp;
  }

  if (a1 > 0 && a2 > 0 && a3 >0)
  {
    printf("Player %s rolls %d %d %d\n", player->name, a1, a2, a3);
  }
  else if (a1 > 0 && a2 > 0)
  {
    printf("Player %s rolls %d %d\n", player->name, a1, a2);
  }
  else if (a1 > 0)
  {
    printf("Player %s rolls %d\n", player->name, a1);
  }

  if (d1 > 0 && d2 > 0)
  {  
    printf("Against           %d %d\n", d1, d2);
  }
  else if (d1 > 0)
  {
    printf("Against           %d\n", d1);
  }
  if (a1 > d1)
  {
    printf("Player %s wins %d against %d\n", player->name, a1, d1);
    selectedTerritoryToInvade->numberOfDefendingTroops -= 1;    
  }
  else
  {
    printf("The defender wins %d against %d\n", d1, a1);
    selectedTerritory->numberOfDefendingTroops -= 1;   
    numberOfInvadingTroops -= 1;
  }

  if (a2 > d2)
  {
    if (a2 > 0)
    {
      printf("Player %s wins %d against %d\n", player->name, a2, d2);
      selectedTerritoryToInvade->numberOfDefendingTroops -= 1;    
    }
  }
  else
  {
    if (a2 > 0)
    {
      printf("The defender wins %d against %d\n", d2, a2);
      selectedTerritory->numberOfDefendingTroops -= 1;
      numberOfInvadingTroops -= 1;   
    }
  }

  if (selectedTerritoryToInvade->numberOfDefendingTroops < 1)
  {
    capturedTerritory = 1;
    printf("Player %s you have conquered %s\n", player->name, selectedTerritoryToInvade->name);
    linkedListAdd(player->occupiedTerritories, selectedTerritoryToInvade);
    Node * p = playerList;
    Player * defendingPlayer = NULL;
    while (p != NULL)
    {
      defendingPlayer = (Player *)p->data;
      printf("Looking at player %s with id: %d\n", defendingPlayer->name, defendingPlayer->id);
      if (defendingPlayer->id == selectedTerritoryToInvade->occupiedById)
      {
        printf("\nPlayer %s loses %s\n",defendingPlayer->name, selectedTerritoryToInvade->name);
        selectedTerritoryToInvade->occupiedBy = player->name;
        selectedTerritoryToInvade->occupiedById = player->id;
        selectedTerritoryToInvade->numberOfDefendingTroops = numberOfInvadingTroops;
        selectedTerritory->numberOfDefendingTroops -= numberOfInvadingTroops;
        printf("\n\nDefending player %s's occupied territories\n", defendingPlayer->name);
        Node * pp = defendingPlayer->occupiedTerritories;
        Node * nodeToRemove = NULL;
        while (pp != NULL)
        {
           Territory * tt = (Territory*)pp->data;
           printf("     %s\n", tt->name);
           if (tt->id == selectedTerritoryToInvade->id)
           {
             printf("Removing: %s\n", tt->name);
             nodeToRemove = pp;
           }
          pp = pp->next; 
        }
        linkedListRemove(defendingPlayer->occupiedTerritories, nodeToRemove);  
        
        printf("\nDefending player %s's occupied territories after the lost territory is removed.\n", defendingPlayer->name);
        pp  = defendingPlayer->occupiedTerritories;
        while (pp != NULL)
        {
           Territory * tt = (Territory*)pp->data;
          printf("%s\n", tt->name);
          pp = pp->next; 
        }
        break;
      }
      p = p->next;
    }
    
  }

   printf("Player %s do you want to attack again? (y/n)\n", player->name);
   scanf ("%[^\n]%*c", buffer);
   if (!(buffer[0] == 'y' || buffer[0] == 'Y'))
   {
     attack = 0;
     int numberOfTroops = 3; // receive three new troops at the end of every turn
     // calculate new troops
     if (capturedTerritory > 0)
     {
        // receive card   
     }
     
     // reallocate troops to territories
     while (numberOfTroops > 0)
     {
     pp  = player->occupiedTerritories;
     while (pp != NULL)
     {
       Territory * tt = (Territory*)pp->data;
       printf("%s has %d troops and you have %d undeployed troops\n", tt->name, tt->numberOfDefendingTroops, numberOfTroops);
       printf("Enter the number of troops to add (negative to remove)");
       scanf ("%[^\n]%*c", buffer);
       int numberToAdd = atoi(buffer);
       if (numberToAdd < 0 && -1*numberToAdd <= tt->numberOfDefendingTroops)
       {
        tt->numberOfDefendingTroops -= numberToAdd;
        numberToAdd += -1*numberToAdd; 
       } 
       else if (numberToAdd > 0 && numberToAdd <= numberOfTroops)
       {
         tt->numberOfDefendingTroops += numberToAdd;
       }
       pp = pp->next; 
     }
     }
   }
  }
}



int main (int argc,	 char * argv)
{
  srand (time(NULL));
  printf ("************  Risk  ************\n");

  Player * player = malloc(sizeof(Player));
  player->name = "black";
  player->id = 1;
  Node * playerList = linkedListCreate(player);
  player = malloc(sizeof(Player));
  player->name = "blue";
  player->id = 2;
  linkedListAdd(playerList, player);  

  player = malloc(sizeof(Player));
  player->name = "green";
  player->id = 3;
  linkedListAdd(playerList, player);

  player = malloc(sizeof(Player));
  player->name = "pink";
  player->id = 4;
  linkedListAdd(playerList, player);

  player = malloc(sizeof(Player));
  player->name = "red";
  player->id = 5;
  linkedListAdd(playerList, player);

  player = malloc(sizeof(Player));
  player->name = "yellow";
  player->id = 6;
  linkedListAdd(playerList, player);

  HashMap * territoryMap = hashMapCreate(41);
  HashMap * northAmericaMap = hashMapCreate(13);
  HashMap * southAmericaMap = hashMapCreate(13);
  HashMap * africaMap = hashMapCreate(13);
  HashMap * europeMap = hashMapCreate(13);
  HashMap * asiaMap = hashMapCreate(13);
  HashMap * australiaMap = hashMapCreate(13);
  Territory * territory = malloc(sizeof(Territory));
  int id = 0;
  Node * territoryList = linkedListCreate(territory);
  territory->name = "alaska";
  territory->id = id++;
  territory = malloc(sizeof(Territory));
  territory->name = "northwest territory";
  territory->id = id++;
  linkedListAdd(territoryList, territory);
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "alberta";
  territory->id = id++;
  linkedListAdd(territoryList, territory);
  hashMapPut(northAmericaMap, territory->name,  territory);


  territory = malloc(sizeof(Territory));
  territory->name = "ontario";
  territory->id = id++;
  linkedListAdd(territoryList, territory);
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "eastern canada";
  territory->id = id++;
  linkedListAdd(territoryList, territory);
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "western united states";
  territory->id = id++;
  linkedListAdd(territoryList, territory);
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "eastern united states";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "central america";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "venezuela";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(southAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "peru";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(southAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "brazil";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(southAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "argentina";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(southAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "greenland";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(northAmericaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "iceland";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "great britain";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "north africa";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(africaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "egypt";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(africaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "east africa";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(africaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "central africa";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(africaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "south africa";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(africaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "madagascar";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(africaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "middle east";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "western europe";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "northern europe";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "scandinavia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "russia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "afghanistan";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "ural";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "siberia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "india";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "southeast asia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "china";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "mongolia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "japan";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "yakutsk";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "kamchatka";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(asiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "new guinea";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(australiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "indonesia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(australiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "eastern australia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(australiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "western australia";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(australiaMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "southern europe";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(europeMap, territory->name,  territory);

  territory = malloc(sizeof(Territory));
  territory->name = "irkutsk";
  territory->id = id++;
  linkedListAdd(territoryList, territory);  
  hashMapPut(australiaMap, territory->name,  territory);
   
  Node * p = territoryList;
  Territory * t = NULL;
  while (p != NULL)
  {
    t = ((Territory*)(p->data));
    hashMapPut(territoryMap, t->name, t);
    printf("Territory: %s\n", t->name);
    initializeTerritory(t, t->id, t->name);
    p = p->next;
  }

  t = (Territory*)hashMapGet(territoryMap, "alaska");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "northwest territory")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "alberta")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "kamchatka")); 

  t = (Territory*)hashMapGet(territoryMap, "northwest territory");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "alaska")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "greenland")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ontario"));   
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "alberta")); 

  t = (Territory*)hashMapGet(territoryMap, "alberta");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "alaska")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "western united states")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ontario"));   
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northwest territory")); 

  t = (Territory*)hashMapGet(territoryMap, "greenland");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "northwest territory")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern canada")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ontario"));   
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "iceland")); 

  t = (Territory*)hashMapGet(territoryMap, "central america");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "western united states")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern united states")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "venezuela"));   

  t = (Territory*)hashMapGet(territoryMap, "western united states");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "alberta")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ontario")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern united states"));   
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "central america")); 

  t = (Territory*)hashMapGet(territoryMap, "ontario");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "eastern canada")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern united states")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "western united states")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "alberta"));   
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "greenland")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northwest territory")); 
  t = (Territory*)hashMapGet(territoryMap, "eastern canada");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "eastern united states")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ontario"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "greenland")); 

  t = (Territory*)hashMapGet(territoryMap, "venezuela");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "central america")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "brazil"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "peru")); 


  t = (Territory*)hashMapGet(territoryMap, "brazil");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "venezuela")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "argentina"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "peru"));     
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "north africa")); 


 t = (Territory*)hashMapGet(territoryMap, "peru");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "venezuela")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "brazil"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "argentina")); 


 t = (Territory*)hashMapGet(territoryMap, "argentina");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "peru")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "brazil"));    


 t = (Territory*)hashMapGet(territoryMap, "iceland");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "greenland")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "great britain"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "scandinavia"));     


 t = (Territory*)hashMapGet(territoryMap, "great britain");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "iceland")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northern europe"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "western europe")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "scandinavia")); 

 t = (Territory*)hashMapGet(territoryMap, "western europe");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "great britain")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northern europe"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "north africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southern europe"));


 t = (Territory*)hashMapGet(territoryMap, "north africa");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "western europe")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "brazil"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "egypt"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "east africa"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "central africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southern europe")); 

 t = (Territory*)hashMapGet(territoryMap, "central africa");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "north africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "south africa"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "east africa")); 


  t = (Territory*)hashMapGet(territoryMap, "south africa");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "central africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "madagascar"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "east africa")); 


 t = (Territory*)hashMapGet(territoryMap, "egypt");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "north africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "east africa"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "middle east")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southern europe"));

 t = (Territory*)hashMapGet(territoryMap, "madagascar");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "east africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "south africa"));    


 t = (Territory*)hashMapGet(territoryMap, "middle east");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "egypt")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "east africa"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southern europe")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "india"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "russia"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "afghanistan"));    


 t = (Territory*)hashMapGet(territoryMap, "russia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "middle east")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "afghanistan"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ural"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "scandinavia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northern europe"));     
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southern europe")); 


 t = (Territory*)hashMapGet(territoryMap, "east africa");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "middle east")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "central africa"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "south africa")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "madagascar"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "egypt"));
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "north africa"));

  t = (Territory*)hashMapGet(territoryMap, "eastern united states");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "central america")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "western united states"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ontario"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern canada"));    

  t = (Territory*)hashMapGet(territoryMap, "northern europe");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "western europe")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "russia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "great britain"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "scandinavia"));      
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southern europe"));     

  t = (Territory*)hashMapGet(territoryMap, "scandinavia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "russia")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "great britain"));      
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "iceland"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northern europe"));

  t = (Territory*)hashMapGet(territoryMap, "ural");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "afghanistan")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "siberia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "china"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "russia")); 

  t = (Territory*)hashMapGet(territoryMap, "afghanistan");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "middle east")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "china"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ural"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "russia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "india"));     

  t = (Territory*)hashMapGet(territoryMap, "siberia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "yakutsk")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "irkutsk"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ural"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "china"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "mongolia"));     

  t = (Territory*)hashMapGet(territoryMap, "india");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "middle east")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "afghanistan"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "china"));     
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southeast asia"));     

  t = (Territory*)hashMapGet(territoryMap, "southeast asia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "india")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "china"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "indonesia"));    


  t = (Territory*)hashMapGet(territoryMap, "china");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "india")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "afghanistan"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "ural"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "siberia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southeast asia"));     
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "mongolia"));

  t = (Territory*)hashMapGet(territoryMap, "mongolia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "japan")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "siberia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "china"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "irkutsk"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "kamchatka"));     
 

  t = (Territory*)hashMapGet(territoryMap, "japan");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "kamchatka")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "mongolia"));    

  t = (Territory*)hashMapGet(territoryMap, "yakutsk");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "kamchatka")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "irkutsk"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "siberia"));    

  t = (Territory*)hashMapGet(territoryMap, "kamchatka");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "japan")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "yakutsk"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "irkutsk"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "mongolia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "alaska"));
  t = (Territory*)hashMapGet(territoryMap, "new guinea");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "indonesia")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern australia"));    

  t = (Territory*)hashMapGet(territoryMap, "eastern australia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "new guinea")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "western australia"));    

  t = (Territory*)hashMapGet(territoryMap, "western australia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "indonesia")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "eastern australia"));    
     
  t = (Territory*)hashMapGet(territoryMap, "southern europe");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "western europe")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "northern europe"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "russia"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "middle east"));
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "egypt"));    

  t = (Territory*)hashMapGet(territoryMap, "irkutsk");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "mongolia")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "siberia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "yakutsk"));  
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "kamchatka"));   


  t = (Territory*)hashMapGet(territoryMap, "indonesia");
  t->adjoiningTerritories = linkedListCreate((Territory*)hashMapGet(territoryMap, "new guinea")); 
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "western australia"));    
  linkedListAdd(t->adjoiningTerritories,(Territory*)hashMapGet(territoryMap, "southeast asia"));
      
  p = territoryList;
  while (p != NULL)
  {
    t = ((Territory*)(p->data));
    printf("Territory: %s\n", t->name);
    Node* pp = t->adjoiningTerritories;
    while (pp != NULL)
    {
      Territory* tt = ((Territory*)(pp->data));
      printf("    %s\n", tt->name);
      pp = pp->next;
    }
    p = p->next;
  }

  p = playerList;
  int playerId = 0;
  while (p != NULL)
  { 
    Player * player = (Player *)p->data;
    initializePlayer(player, player->name);
    player->id = playerId++;
    p = p->next;
  }

  p = playerList;
  while (unoccupiedTerritoryCount(territoryList) > 0)
  { 
    Player * player = (Player *)p->data;
    printf("Player: %s\n", player->name);
    selectUnoccupiedTerritory(territoryList, player);
    p = p->next;
    if (p == NULL)
    {
      p = playerList;
    }
  }
 
  p = playerList;
  while (p != NULL)
  {
    Player * player = (Player *)p->data;
    printf("Territories occupied by player %s with id: %d\n", player->name, player->id);
    Node * pp = player->occupiedTerritories;
    while (pp != NULL)
    {
      t = ((Territory*)(pp->data));
      printf("     %s\n", t->name);
      pp = pp->next;
      
    }
    p = p->next;
  }

  char buffer [100];
  p = playerList;
  while (p != NULL)
  {
    Player * player = (Player *)p->data;
    printf("Territories occupied by player %s\n", player->name);
    Node * pp = player->occupiedTerritories;
    while (pp != NULL && player->numberOfUndeployedTroops > 0)
    {
      t = ((Territory*)(pp->data));
      printf("Enter the number of troops to deploy in %s from 0 to %d\n", t->name, player->numberOfUndeployedTroops);
//      scanf ("%[^\n]%*c", buffer);
      int number = 5;//atoi(buffer);
       while (number < 0 || number > player->numberOfUndeployedTroops)
       {
          printf("Enter the number of troops to deploy in %s from 0 to %d\n", t->name, player->numberOfUndeployedTroops);
          scanf ("%[^\n]%*c", buffer);
          number = 5;//atoi(buffer);
       }
       t->numberOfDefendingTroops = t->numberOfDefendingTroops + number;
       player->numberOfUndeployedTroops -= number;

      pp = pp->next;
      
    }
    p = p->next;
  }

  p = playerList;
  while (p != NULL)
  {
    Player * player = (Player *)p->data;
    printf("Player %s's turn.\n", player->name);
    turn(territoryList, player, playerList);
    p = p->next;
    if (p == NULL)
    {
      p = playerList;
    }
  }

/*
  char buffer [100];
  scanf ("%[^\n]%*c", buffer);
  while (!(buffer[0] == 'q' && buffer[1] == '\0'))
  {
    printf("input: %s\n", buffer);
    int pos = 0;
    while (pos < strlen(buffer))
    {
      pos++; 
    }
    scanf ("%[^\n]%*c", buffer);
  }

  char c = getchar();
  while (c != 10)
  {
    printf("  %d  ", (int)c);
    c = getchar();
  }
*/
}