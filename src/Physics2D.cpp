/*
 * Physics2D.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */


#include <Physics2D.h>
#include <Entity381.h>
#include <Engine.h>
#include <Utils.h>

Physics2D::Physics2D(Entity381* ent):Aspect(ent){

}

Physics2D::~Physics2D(){

}


void Physics2D::Tick(float dt){
		entity->position = entity->position + entity->velocity * dt;

}
