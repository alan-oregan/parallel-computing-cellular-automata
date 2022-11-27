import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

class Visualisation extends JFrame {

    private final int WORLDSIZE = 1000;
    private File[] worldFiles;

    // move to JPanel component https://stackoverflow.com/questions/21121859/how-to-paint-on-a-jpanel

    public Visualisation() {
        worldFiles = new File("../output").listFiles();

        //jFrame
        this.setResizable(false);
        this.setSize(WORLDSIZE, WORLDSIZE);
        this.setLocationRelativeTo(null); // center the window
        this.setVisible(true); // set everything to visible
        this.setDefaultCloseOperation(EXIT_ON_CLOSE); // stop the program on close
    }

    private char[][] readDatFile(String filePath) {
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
        this.paintWorld(g);
    }

    public void paintWorld(Graphics g) {
        g.setColor(Color.ORANGE);
        g.fillRect(10, 0, WORLDSIZE, WORLDSIZE);

        for (File worldFile : worldFiles) {
            System.out.printf("Visualising %s...\n", worldFile.getName());
            runVisualisation(g, readDatFile(worldFile.getPath()));
            try {
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void runVisualisation(Graphics g, char[][] world) {
        for (int i = 0; i < world[0].length; i++) {
            for (int j = 0; j < world.length; j++) {
                g.setColor(
                        switch (world[i][j]) {
                            case 'S' -> Color.ORANGE;
                            case 'E' -> Color.BLUE;
                            case 'I' -> Color.MAGENTA;
                            case 'R' -> Color.GREEN;
                            default -> Color.RED;
                        });

                g.fillRect(i + 2, j, 4, 4);
            }
        }
    }

    public static void main(String[] args) {
        new Visualisation();
    }
}
