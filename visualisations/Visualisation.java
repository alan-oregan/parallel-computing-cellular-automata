import javax.swing.*;
import java.awt.BorderLayout;
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

    // move to JPanel component https://stackoverflow.com/questions/21121859/how-to-paint-on-a-jpanel

    public Visualisation() {
        super("SEIR Model Visualisation");

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
        JLabel label = new JLabel(
                String.format("Visualisation %4s Key: Susceptible-Orange | Exposed-Blue | Infected-Magenta | Recovered-Green",
                    worldFiles.get(0).getName().replaceAll("[^0-9]", "")),
                    SwingConstants.CENTER);

        this.getContentPane().add(label, BorderLayout.NORTH);
        this.getContentPane().add(worldRenderer, BorderLayout.CENTER);

        //jFrame
        this.setResizable(false);
        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        for (File worldFile : worldFiles) {
            System.out.printf("Visualising %s...\n", worldFile.getName());
            worldRenderer.setWorld(readDatFile(worldFile.getPath()));
            worldRenderer.repaint();
            try {
                TimeUnit.SECONDS.sleep(1);
                label.setText(String.format("Visualisation %4s Key: Susceptible-Orange | Exposed-Blue | Infected-Magenta | Recovered-Green",
                        worldFile.getName().replaceAll("[^0-9]", "")));
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
