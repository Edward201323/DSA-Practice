import edu.princeton.cs.algs4.StdRandom;

import java.awt.*;
import java.util.Map;

public class Particle {
    public ParticleFlavor flavor;
    public int lifespan;

    public static final int PLANT_LIFESPAN = 150;
    public static final int FLOWER_LIFESPAN = 75;
    public static final int FIRE_LIFESPAN = 10;
    public static final Map<ParticleFlavor, Integer> LIFESPANS =
            Map.of(ParticleFlavor.FLOWER, FLOWER_LIFESPAN,
                   ParticleFlavor.PLANT, PLANT_LIFESPAN,
                   ParticleFlavor.FIRE, FIRE_LIFESPAN);

    public Particle(ParticleFlavor flavor) {
        this.flavor = flavor;
        if(LIFESPANS.containsKey(flavor)){
            this.lifespan = LIFESPANS.get(flavor);
        } else {
            this.lifespan = -1;
        }
    }

    public Color color() {
        if (flavor == ParticleFlavor.EMPTY) {
            return Color.BLACK;
        }
        if(flavor == ParticleFlavor.SAND){
            return Color.YELLOW;
        }
        if(flavor == ParticleFlavor.BARRIER){
            return Color.GRAY;
        }
        if(flavor == ParticleFlavor.WATER){
            return Color.BLUE;
        }
        if(flavor == ParticleFlavor.FOUNTAIN){
            return Color.CYAN;
        }
        if (flavor == ParticleFlavor.FLOWER) {
            double ratio = (double) Math.max(0, Math.min(lifespan, FLOWER_LIFESPAN)) / FLOWER_LIFESPAN;
            int r = 120 + (int) Math.round((255 - 120) * ratio);
            int g = 70 + (int) Math.round((141 - 70) * ratio);
            int b = 80 + (int) Math.round((161 - 80) * ratio);
            return new Color(r, g, b);
        }
        if (flavor == ParticleFlavor.PLANT) {
            double ratio = (double) Math.max(0, Math.min(lifespan, PLANT_LIFESPAN)) / PLANT_LIFESPAN;
            int g = 120 + (int) Math.round((255 - 120) * ratio);
            return new Color(0, g, 0);
        }
        if (flavor == ParticleFlavor.FIRE) {
            double ratio = (double) Math.max(0, Math.min(lifespan, FIRE_LIFESPAN)) / FIRE_LIFESPAN;
            int r = (int) Math.round(255 * ratio);
            return new Color(r, 0, 0);
        }


        return Color.GRAY;
    }

    public void moveInto(Particle other) {
        other.flavor = this.flavor;
        other.lifespan = this.lifespan;

        this.flavor = ParticleFlavor.EMPTY;
        this.lifespan = -1;
    }

    public void fall(Map<Direction, Particle> neighbors) {
        Particle below = neighbors.get(Direction.DOWN);

        if(below.flavor == ParticleFlavor.EMPTY) {
            this.moveInto(below);
        }
    }

    public void flow(Map<Direction, Particle> neighbors) {
        int rand = StdRandom.uniformInt(3);
        if(rand == 0){
            return;
        }
        if(rand == 1){
            Particle left = neighbors.get(Direction.LEFT);
            if(left.flavor == ParticleFlavor.EMPTY){
                this.moveInto(left);
            }
        }
        if (rand == 2){
            Particle right = neighbors.get(Direction.RIGHT);
            if(right.flavor == ParticleFlavor.EMPTY){
                this.moveInto(right);
            }
        }
    }

    public void grow(Map<Direction, Particle> neighbors) {
        int rand = StdRandom.uniformInt(10); // gives 0 -> 9
        if(rand == 0){
            Particle up = neighbors.get(Direction.UP);
            if(up.flavor == ParticleFlavor.EMPTY){
                up.flavor = this.flavor;
                up.lifespan = LIFESPANS.get(this.flavor);
            }
        }
        if(rand == 1){
            Particle left = neighbors.get(Direction.LEFT);
            if(left.flavor == ParticleFlavor.EMPTY){
                left.flavor = this.flavor;
                left.lifespan = LIFESPANS.get(this.flavor);
            }
        }
        if(rand == 2){
            Particle right = neighbors.get(Direction.RIGHT);
            if(right.flavor == ParticleFlavor.EMPTY){
                right.flavor = this.flavor;
                right.lifespan = LIFESPANS.get(this.flavor);
            }
        }
    }

    private void burner(Particle particle){
        if(particle.flavor == ParticleFlavor.PLANT || particle.flavor == ParticleFlavor.FLOWER) {
            if(StdRandom.uniformInt(10) < 4){
                particle.flavor = ParticleFlavor.FIRE;
                particle.lifespan = FIRE_LIFESPAN;
            }
        }
    }

    public void burn(Map<Direction, Particle> neighbors) {
        burner(neighbors.get(Direction.UP));
        burner(neighbors.get(Direction.DOWN));
        burner(neighbors.get(Direction.LEFT));
        burner(neighbors.get(Direction.RIGHT));
    }

    public void action(Map<Direction, Particle> neighbors) {
        if(this.flavor == ParticleFlavor.EMPTY){
            return;
        }
        if(this.flavor != ParticleFlavor.BARRIER){
            this.fall(neighbors);
        }
        if(this.flavor == ParticleFlavor.WATER){
            this.flow(neighbors);
        }
        if(this.flavor == ParticleFlavor.PLANT || this.flavor == ParticleFlavor.FLOWER){
            this.grow(neighbors);
        }
        if(this.flavor == ParticleFlavor.FIRE){
            this.burn(neighbors);
        }
    }

    public void decrementLifespan(){
        if (this.lifespan > 0) {
            this.lifespan -= 1;
        }
        if(this.lifespan == 0){
            this.flavor = ParticleFlavor.EMPTY;
            this.lifespan = -1;
        }
    }
}