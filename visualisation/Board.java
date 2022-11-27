import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JPanel;

public class Board extends JPanel {

    private static final int DIM_WIDTH = 640;
    private static final int DIM_HEIGHT = 640;
    private static final int SQ_SIZE = 80;

    boolean black = true;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (int i = 0; i < DIM_HEIGHT; i += SQ_SIZE) {
            if (black) {
                black = false;
            } else {
                black = true;
            }
            for (int j = 0; j < DIM_WIDTH; j += SQ_SIZE) {
                if (black) {
                    g.setColor(Color.WHITE);
                    g.fillRect(j, i, SQ_SIZE, SQ_SIZE);
                    black = false;
                } else {
                    g.setColor(Color.BLACK);
                    g.fillRect(j, i, SQ_SIZE, SQ_SIZE);
                    black = true;
                }
            }
        }
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(DIM_WIDTH, DIM_HEIGHT);
    }
}