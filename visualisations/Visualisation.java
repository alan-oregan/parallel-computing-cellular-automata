import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.List;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

class Visualisation extends JFrame {

    private final int WORLDSIZE = 1000;

    public Visualisation() {
        super("SEIR Model Visualisation");
        Font primaryFont = new Font("Arial", Font.BOLD, 18);
        JPanel labelPanel = new JPanel();

        List<File> worldFiles = Arrays.asList(new File("../output").listFiles());
        worldFiles = worldFiles.stream()
                .sorted(
                        new Comparator<File>() {
                            @Override
                            public int compare(File o1, File o2) {
                                return Integer.parseInt(o1.getName().replaceAll("[^0-9]", ""))
                                        - Integer.parseInt(o2.getName().replaceAll("[^0-9]", ""));
                            }
                        })
                .collect(Collectors.toList());


        WorldRenderer worldRenderer = new WorldRenderer();

        JLabel keyLabel = new JLabel(
                "Key: Susceptible-Orange | Exposed-Blue | Infected-Magenta | Recovered-Green",
                SwingConstants.CENTER
        );

        JLabel numLabel = new JLabel("Generation: 0", SwingConstants.CENTER);

        keyLabel.setFont(primaryFont);
        numLabel.setFont(primaryFont);

        labelPanel.setLayout(new GridLayout(2,0));
        labelPanel.add(keyLabel);
        labelPanel.add(numLabel);

        this.getContentPane().add(labelPanel, BorderLayout.NORTH);
        this.getContentPane().add(worldRenderer, BorderLayout.CENTER);

        //jFrame
        this.setResizable(false);
        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        // Visualise Files
        for (File worldFile : worldFiles) {
            System.out.printf("Visualising %s...\n", worldFile.getName());
            worldRenderer.setWorld(readDatFile(worldFile.getPath()));
            worldRenderer.repaint();
            try {
                numLabel.setText("Generation: " + worldFile.getName().replaceAll("[^0-9]", ""));
                TimeUnit.SECONDS.sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
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

    public static void main(String[] args) {
        new Visualisation();
    }
}
