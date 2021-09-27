package src_galvez_obispo_javier;

import ontology.Types.ACTIONS;
import tools.Vector2d;

public class Nodo implements Comparable<Nodo>{
	public Vector2d position;
	public int cost;
	public int heuristic;
	public ACTIONS action;
	public Vector2d direction;
	public Nodo parent;
	
	public Nodo() {
		position = new Vector2d();
		cost = 0;
		heuristic = 0;
		action = ACTIONS.ACTION_NIL;
		direction = new Vector2d();
		parent = null;
	}
	
	public Nodo(Nodo n) {
		this.position = new Vector2d(n.position);
		this.cost = n.cost;
		this.direction = new Vector2d(n.direction);
		this.parent = n;
	}
	
	@Override
	public int compareTo(Nodo n) {
		return (this.cost + this.heuristic) - (n.cost + n.heuristic);
	}
	
	@Override
	public boolean equals(Object o) {
		if(o instanceof Nodo) {
			Nodo n = (Nodo) o;
			return this.position.equals(n.position) && this.direction.equals(n.direction);
		} else {
			return false;
		}
	}
	
	@Override
	public int hashCode() {
		return (int)(position.x * 100 + position.y);
	}
}
