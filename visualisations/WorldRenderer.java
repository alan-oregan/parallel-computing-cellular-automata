import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JPanel;

public class WorldRenderer extends JPanel {

    private static final int SIM_SIZE = 1000;
    private char[][] world = null;
    private Color[] colors = { Color.orange, Color.blue, Color.magenta, Color.green };

    public WorldRenderer(){};

    public WorldRenderer(Color[] colors) {
        this.colors = colors;
    }

    public Color[] getColors() {
        return colors;
    }

    public void setColors(Color[] colors) {
        this.colors = colors;
    }

    public char[][] getWorld() {
        return world;
    }

    public void setWorld(char[][] world) {
        this.world = world;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(colors[0]);
        g.fillRect(0, 0, SIM_SIZE, SIM_SIZE);
        if (world != null) {
            for (int i = 0; i < world[0].length; i++) {
                for (int j = 0; j < world.length; j++) {
                    if (world[i][j] != 'S') {
                        switch (world[i][j]) {
                            case 'R':
                                g.setColor(colors[3]);
                                break;
                            case 'E':
                                g.setColor(colors[1]);
                                break;
                            case 'I':
                                g.setColor(colors[2]);
                                break;
                        };
                        g.drawLine(i, j, i, j);
                    }
                }
            }
        }
    }

    public Dimension getPreferredSize() {
        return new Dimension(SIM_SIZE, SIM_SIZE);
    }
}