import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Visualisation extends JFrame {

    private final int WORLDSIZE = 1000;
    private char[][] currentWorld;

    // move to JPanel component https://stackoverflow.com/questions/21121859/how-to-paint-on-a-jpanel 

    public Visualisation() {
        currentWorld = readLetterCount("../output/world_400.dat");

        //jFrame
        this.setResizable(false);
        this.setSize(WORLDSIZE, WORLDSIZE);
        this.setLocationRelativeTo(null); // center the window
        this.setVisible(true); // set everything to visible
        this.setDefaultCloseOperation(EXIT_ON_CLOSE); // stop the program on close
    }

    private char[][] readLetterCount(String filePath) {
        char[][] world = new char[WORLDSIZE][WORLDSIZE];

        try {
            Scanner scanner = new Scanner(new File(filePath));
            int i = 0;
            while (scanner.hasNextLine()) {
                world[i++] = scanner.nextLine().toCharArray();
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        return world;
    }

    public void paint(Graphics g) {
        super.paint(g);
        this.paintWorld(g, currentWorld);
    }

    public void paintWorld(Graphics g, char[][] world) {
        g.setColor(Color.GREEN);
        g.fillRect(10, 0, WORLDSIZE, WORLDSIZE);

        for (int i = 0; i < world.length; i++) {
            for (int j = 0; j < world[0].length; j++)
            {
                g.setColor(
                    switch (world[i][j]) {
                        case 'S' -> Color.GREEN;
                        case 'E' -> Color.BLUE;
                        case 'I' -> Color.MAGENTA;
                        case 'R' -> Color.ORANGE;
                        default -> Color.BLUE;
                    }
                );

                g.fillRect(i+2, j, 4, 4);
            }
        }
    }

    public static void main(String[] args) {
        new Visualisation();
    }
}
