package src_galvez_obispo_javier;

import java.util.ArrayList;
import java.util.Arrays;

import core.game.Observation;
import core.game.StateObservation;
import tools.ElapsedCpuTimer;
import ontology.Types.ACTIONS;
import core.player.AbstractPlayer;
import tools.Vector2d;
import tools.Pair;

public class Agent extends AbstractPlayer{
	int blockSize;
	
	Vector2d portal;
	ArrayList<Pair<Vector2d, Integer> > diamantes;
	
	Pathfinder pathfinder;
	ArrayList<ACTIONS> camino;
	int pasos_dados;
	boolean recalcular_camino = true;
	boolean inDangerRecently = false;
	
	int[][] heatMap;
	
	public Agent(StateObservation stateObs, ElapsedCpuTimer elapsedTimer){
		
		blockSize = stateObs.getBlockSize();
      
        portal = transformPoint(stateObs.getPortalsPositions()[0].get(0).position);
        pathfinder = new Pathfinder(stateObs);
        camino = new ArrayList<ACTIONS>();
        pasos_dados = 0;
    
        diamantes = new ArrayList<Pair<Vector2d, Integer> >();
        if(stateObs.getResourcesPositions() != null) {
	        for(Observation obs : stateObs.getResourcesPositions()[0]) {
	        	Vector2d dPos = transformPoint(obs.position);
	        	Pair<Vector2d, Integer> d = new Pair<Vector2d, Integer>(dPos, 0);
	        	diamantes.add(d);
	        }
        }
        
        heatMap = new int[stateObs.getObservationGrid().length][stateObs.getObservationGrid()[0].length];

	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		ACTIONS accion = ACTIONS.ACTION_NIL;
		
		Vector2d aPos = transformPoint(stateObs.getAvatarPosition());
		Nodo start = new Nodo();
		start.position = aPos;
		start.direction = stateObs.getAvatarOrientation();
		
		if(!diamantes.isEmpty() && start.position.equals(diamantes.get(0).getKey()))
			diamantes.remove(0);		
		
		updateHeatMap(stateObs.getNPCPositions());
		boolean inDanger = (heatMap[(int) aPos.x][(int) aPos.y] != 0);

		if(inDanger) {
			ArrayList<Vector2d> enemies = new ArrayList<Vector2d>();
			for(Observation obs : stateObs.getNPCPositions(stateObs.getAvatarPosition())[0]) {
				enemies.add(new Vector2d(transformPoint(obs.position)));
			}
			camino = pathfinder.runAway(start, enemies, heatMap[(int) aPos.x][(int) aPos.y]);
			recalcular_camino = false;
			inDangerRecently = true;
			pasos_dados = 0;
		}

		else {
			if(inDangerRecently) {
				inDangerRecently = false;
				recalcular_camino = true;
			}
			if(pasos_dados == 6) {
				recalcular_camino = true;
			}
			if(recalcular_camino){
				pasos_dados = 0;
				Vector2d goal = new Vector2d();
				if(!diamantes.isEmpty() && stateObs.getGameScore()!=20) {
					sortDiamantes(start.position);
					goal = diamantes.get(0).getKey();
				} else {
					goal = portal;
				}
				
				camino = pathfinder.astar(start, goal);
			}
		}
		
		accion = camino.get(0);
		camino.remove(0);
		pasos_dados++;
		
		recalcular_camino = camino.isEmpty();

		return accion;
	}
	
	public Vector2d transformPoint(Vector2d p) {
		Vector2d aux = new Vector2d(p);
		aux.x = aux.x / blockSize;
		aux.y = aux.y / blockSize;
		return aux;
	}
	
	void sortDiamantes(Vector2d ref) {
		for(Pair<Vector2d, Integer> d : diamantes) {
			d.setValue(pathfinder.manhattan(d.getKey(), ref));
		}
        diamantes.sort((p1, p2) -> p1.getValue().compareTo(p2.getValue()));
	}
	
	void updateHeatMap(ArrayList<Observation>[] enemies) {
        for(int[] row : heatMap)
        	Arrays.fill(row, 0);
        
		if(enemies != null) {
			for(Observation obs : enemies[0]) {
				Vector2d ePos = transformPoint(obs.position);
		        int[] x_range = new int[]{0, 0, 0,-1, 1, 0, 0,-2, 2,-1, 1,-1, 1, 0, 0,-3, 3,-2,-1, 1, 2,-2,-1, 1, 2};
		        int[] y_range = new int[]{0,-1, 1, 0, 0,-2, 2, 0, 0,-1,-1, 1, 1,-3, 3, 0, 0, 1, 2, 2, 1,-1,-2,-2,-1};
		        
		        for(int i = 0; i < x_range.length; i++) {
		        	int x = (int) ePos.x + x_range[i];
		        	int y = (int) ePos.y + y_range[i];
		        	if(!(x < 0 || x >= heatMap.length || y < 0 || y >= heatMap[0].length))
		        		heatMap[x][y] += 1;
		        } 	
			}
		}
		pathfinder.heatMap = this.heatMap;
	}
}
