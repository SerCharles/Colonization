/*
Filename: UAnimal.h
Description: the father class of all animals
Version: 1.1
Date: 09/02/2018
*/
#ifndef UANIMAL_H
#define UANIMAL_H
#include <QObject>
#include "uunit.h"

class UAnimal:public UUnit
{
    Q_OBJECT
public:
    //constants of all animals
    const double m_cHungryPointFull{1.0};       //The max hungry point of any animal
    const double m_cEatRatio{0.5};              //The hungry point when animals begin to pray
    const double m_cHungryRatio{0.2};           //The hungry point when animals are hungry
    const double m_cHungryDecrease{0.002};      //The decrement of hungry point per turn
    const int m_cProduceThreshold{100};         //The value Threshold of production
    const double m_cWanderSpeedRatio{0.2};      //The ratio of speednow/speedfull when wandering
    const int m_cShowTimeAfterDeath{50};       //The time showing picture after death


protected:
    //What do not change in a game
    int m_MoneyProduct;         //The money production per turn
    int m_MaterialProduct;      //The material production per turn
    int m_HealthAdd;            //Health increment after eatting it
    double m_HungryPointAdd;    //HungryPoint increment after eatting it
    QPixmap* m_PictureHungry;   //The picture of an animal when it is hungry
    QPixmap* m_PictureDead;     //Death Picture

    //What changes in a game
    int m_ProduceValue;         //Value accumulated to judge production
    int m_TimeAfterDeath;       //Time after it is dead;
    double m_HungryPoint;       //HungryPoint of an animal

public:
    int m_Species;              //The type of animal's species   1:grasseat 2:small_meateat 3:big_meateat
    int m_Status;               //Status of an animal, 1:full 2:foraging 3:hungry 4:dead
    int m_Level;                //the level of the animal

protected:
    /*
     * function: update the picture shown by the unit according to its status
     * */
    void m_UpdatePicture();


    /*
     * function:update the status of the animal after death: do not move, show dead picture for a minute
     * */
    void m_UpdateDeath();


    /*
     * function: update the hungry point of the animal, and change its status according to the hungry point
     * addon: animalking does not get hungry
     */
    virtual void m_UpdateHungry();


    /*
     *function: update the health and death of an animal
     */
    void m_UpdateHealth();


    /*
     *function: update the produce of an animal
     * addon:different animals produce different things: mothers produce animals, others produce bonuses
     */
    virtual void m_UpdateProduce();

public:
    UAnimal():m_HungryPoint(m_cHungryPointFull),m_ProduceValue(0){}
    ~UAnimal(){}

public:
    /*function: the collection of all the update functions, update the status of animals:full, normal, hunrgy, dead
     * the public interface, used in the mainloop to update animal information
     * */
    virtual void m_UpdateStatus();

    /*function: generate a random direction, and the animal will go slowly in the direction
     * use:when the animal is full, or there is no food in its sight
     * public interface, used in the mainloop to update animal movement
    */
    void m_Wander();


    /*function: animal go fast to eat
     * use:when the animal is not full, and there is food nearby
     * addon:the speed of animal will increase when it is more hungry
     * variables:final_x, final_y is the place of the nearest food, which is the animal's destination
     * public interface, used in the mainloop to update animal movement
    */
    void m_Forage(const int final_x, const int final_y);


    /*The public interface giving the animal's healthadd and hungrypointadd to its predator
     *use:when the animal is eaten
     * variables:health_add and hungry_add will be the animal's m_HealthAdd and m_HungryAdd points
    */
    void m_GiveFood(int* health_add, double* hungry_add);


    /*the public interface in managing eating, set the animal invalid, and it will be deleted later in the main loop
     * use: when the animal is eaten
     * */
    void m_BeingEaten();


    /*the public interface in managing eating, add the animal's health and hungry point according to food
     * use:when the animal eats something
     * variables:health_add and hungry_point_add is the increment of the animal's health and hungrypoint after eating something
     * addon: some animals add experiences after eatting food, so the function is overrided
     * */
    virtual void m_EatFood(const int health_add, const double hungry_point_add);



    /*the public interface in managing being attack
     * use:when the animal is attacked
     * variables:the damage the animal taken
     * */
    void m_BeingAttack(const int damage);


    /*
     * function that outputs the species, health ,hungrypoint, producevalue,place into a file
     * use: when saving a game file
     * variable: the file the game will be saved on
     * addon: some animals also need to save their levels and experiences
     */
    virtual void m_OutPut(QString file);
signals:

    /*
     * when an animal can produce a bonus, it emits the signal to produce the bonus
     * */
    void m_BonusProduced(const int money_produce, const int material_produce, const int place_x,const int place_y);
    
    
};
#endif // UANIMAL_H

