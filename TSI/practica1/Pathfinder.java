package src_galvez_obispo_javier;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.PriorityQueue;

import core.game.Observation;
import core.game.StateObservation;
import tools.Direction;
import tools.Vector2d;
import ontology.Types.ACTIONS;
import ontology.Types;

public class Pathfinder {
	public int width, height;
	public ArrayList<Observation> grid[][];
	public int[][] heatMap;
	
	public Pathfinder(StateObservation stateObs) {
		width = stateObs.getObservationGrid().length;
		height = stateObs.getObservationGrid()[0].length;
		grid = stateObs.getObservationGrid();
	}
	
	public int manhattan(Vector2d x1, Vector2d x2) {
		// distancia Manhattan
		return (int) (Math.abs(x1.x - x2.x) + Math.abs(x1.y - x2.y));
	}
	
	public ArrayList<ACTIONS> calc_path(Nodo n){
		ArrayList<ACTIONS> path = new ArrayList<ACTIONS>();
		while(n != null) {
			if(n.parent != null)
				path.add(0, n.action);
			n = n.parent;
		}
		return path;
	}
	
	public boolean isObstacle(Vector2d p) {
		if(p.x<0 || p.x>=width) return true;
		if(p.y<0 || p.y>=height) return true;
		
        for(Observation obs : grid[(int)p.x][(int)p.y])
        {
            if(obs.itype == 0)
                return true;
        }
		return false;
	}
	
	public ArrayList<Nodo> calc_neighbours(Nodo n){
		//up, down, left, right
        int[] x = new int[]{0,    0,    -1,    1};
        int[] y = new int[]{-1,   1,     0,    0};
        ArrayList<Nodo> neighbours = new ArrayList<Nodo>();
        
        for(int i = 0; i < x.length; i++) {
        	Nodo neighbour = new Nodo(n);
        	
        	if(n.direction.x == x[i] && n.direction.y == y[i]) {
	        	neighbour.position.x += x[i];
	        	neighbour.position.y += y[i];
        	}
        	
        	if(!isObstacle(neighbour.position)) {
        		Direction d = Types.DNONE;
	        	switch (i) {
	        	case 0:
	        		neighbour.action = ACTIONS.ACTION_UP;
	        		d = Types.DUP;
	        		break;
	        	case 1:
	        		neighbour.action = ACTIONS.ACTION_DOWN;
	        		d = Types.DDOWN;
	        		break;
	        	case 2:
	        		neighbour.action = ACTIONS.ACTION_LEFT;
	        		d = Types.DLEFT;
	        		break;
	        	case 3:
	        		neighbour.action = ACTIONS.ACTION_RIGHT;
	        		d = Types.DRIGHT;
	        		break;
	        	}

        		neighbour.direction.x = d.x();
        		neighbour.direction.y = d.y();
	        	neighbour.cost += 1 + heatMap[(int) neighbour.position.x][(int) neighbour.position.y];
	        	
	        	neighbours.add(neighbour);
        	}
        }
        
        return neighbours;
	}
	
	public ArrayList<ACTIONS> astar(Nodo start, Vector2d goal){
		if(start.position.equals(goal)) {
			ArrayList<ACTIONS> aux = new ArrayList<ACTIONS>();
			aux.add(ACTIONS.ACTION_NIL);
			return aux;
		}
		
		HashSet<Nodo> generados = new HashSet<Nodo>();
		PriorityQueue<Nodo> abiertos = new PriorityQueue<Nodo>();
		
		Nodo current = start;
		current.heuristic = manhattan(start.position, goal);
		
		abiertos.add(current);
		
		while(!abiertos.isEmpty()) {
			current = abiertos.poll();
			
			if(current.position.equals(goal))
				return calc_path(current);
			
			generados.add(current);
			
			ArrayList<Nodo> neighbours = calc_neighbours(current);
			for(Nodo n : neighbours) {
				if(!generados.contains(n)) {
					n.heuristic = manhattan(n.position, goal);
					abiertos.add(n);
				}
			}
		}
			
		return calc_path(current); 
	}
	
	
	public ArrayList<ACTIONS> runAway(Nodo start, ArrayList<Vector2d> enemies, int num_enemies) {

		Vector2d goal = new Vector2d();
		double degree = 0;
		
		if(num_enemies == 1) {
			Vector2d enemy = enemies.get(0);
			degree = Math.toDegrees(Math.atan2((start.position.y-enemy.y),(start.position.x-enemy.x)));
		} else if(num_enemies == 2) {
			Vector2d enemy1 = new Vector2d(enemies.get(0));
			Vector2d enemy2 = new Vector2d(enemies.get(1));
			
			double degree1 = Math.toDegrees(Math.atan2((start.position.y-enemy1.y),(start.position.x-enemy1.x)));
			double degree2 = Math.toDegrees(Math.atan2((start.position.y-enemy2.y),(start.position.x-enemy2.x)));
			
			degree = degree1;
			if(degree1 > degree2) {
				double aux = degree2;
				degree2 = degree1;
				degree1 = aux;
			}
			
			if(degree1 >= 0  && degree1 <= 90 && degree2 >= 90) {
				degree = 90;
				if(degree1 == 0 && degree2 == 180 && start.position.y >= height/2)
					degree = -90;
			} else if(degree2 <= 0 && degree2 >= -90 && degree1 <= -90) {
				degree = -90;
			} else if(degree2 == 90 && degree1 == -90) {
				if(start.position.x >= width/2) degree = 180;
				else degree = 0;
			}
		}

		// Enemigo por arriba
		if (degree >= 0) {
			goal.y = height-2;
			if(degree > 90) goal.x = 1;
			else goal.x = width-2;
			
			// Agente pegado al borde de abajo
			if(start.position.y > height-5) {
				// Pegado a la esquina izquierda
				if(start.position.x < 4) {
					if(degree > 135) goal.y = 1;
					else if (degree > 90) goal.x = width-2;
				}
				// Pegado a la esquina derecha
				else if(start.position.x > width-5) {
					if(degree > 45) goal.x = 1;
					else if(degree > 0) goal.y = 1;
				}
			}
		}
		// Enemigo por abajo
		else {
			goal.y = 1;
			if(degree > -90) goal.x = width-2;
			else goal.x = 1;
			
			// Agente pegado al borde de arriba
			if(start.position.y < 4) {
				// Pegado a la esquina izquierda
				if(start.position.x < 4) {
					if(degree > -135) goal.x = width-2;
					else goal.y = height-2;
				}
				// Pegado a la esquina derecha
				else if(start.position.x > width-5) {
					if(degree < -45) goal.x = 1;
					else goal.y = height-2;
				}
			}
		}
			
		return astar(start, goal);
	}
}
