package lab2.mathematics;

import java.io.FileWriter;

public abstract class Writable {

    private FileWriter writer;

    public void setWriter(final FileWriter writer){
        this.writer = writer;
    }

    protected void tryWriteToFile(final String... data){
        if(writer != null){
            try {
                writer.write(String.join(",", data) + "\n");
            }catch (Exception e){
                return;
//                throw new Error("Не удалось записать в файл");
            }
        }
    }
}
