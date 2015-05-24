import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.HashMap;

public class HuffmanCodeTester {

    public static void main(String[] args) {
        HuffmanCoder coder = new HuffmanCoder();
        coder.decode("coded.txt", "decoded.txt");
    }
}


class HuffmanCoder {

    private int decodeCountBits;
    private int decodeCountSymbols;
    private HashMap<CustomBitSet, Character> decodeCodeToSymbol;
    private StringBuilder codedText;
    private StringBuilder decodedText;

    public void decode(String inputFileName, String outputFileName) {
        decodeInputData(inputFileName);
        decodeSolve();
        decodeOutputData(outputFileName);
    }

    private void decodeInputData(String inputFileName) {
        decodeCodeToSymbol = new HashMap<CustomBitSet, Character>();
        try {
            FileInputStream reader = new FileInputStream(new File(inputFileName));

            decodeCountSymbols = readNumber(reader);

            for (int i = 0; i < decodeCountSymbols; ++i) {
                String currentCodeString = readBinaryString(reader);
                CustomBitSet currentCode = CustomBitSet.fromString(currentCodeString);

                char currentSymbol = (char) reader.read();
                reader.read();

                decodeCodeToSymbol.put(currentCode, currentSymbol);
            }

            decodeCountBits = readNumber(reader);

            codedText = new StringBuilder();
            readTextByte(codedText, reader);
        }
        catch (IOException IOex) {
            System.err.println(IOex.getStackTrace());
        }
    }

    private void decodeSolve() {
        decodingText();
    }

    private void decodeOutputData(String outputFileName) {

        try {
            FileOutputStream writer = new FileOutputStream(new File(outputFileName));
            ArrayList<Byte> outputArrayList = new ArrayList<Byte>();
            makeDecodedOutputArrayList(outputArrayList);

            outputBytes(writer, outputArrayList);
            writer.close();
        }
        catch (IOException IOex) {
            System.err.print(IOex.getStackTrace());
        }
    }

    // input/output finctions

    private void readTextByte(StringBuilder text, FileInputStream reader) throws IOException {
        // due to too frequent access to the file
        byte[] bytes = new byte[1024];
        int count = reader.read(bytes);

        while (count != -1) {
            for (int i = 0; i < count; ++i) {
                text.append((char) bytes[i]);
            }
            count = reader.read(bytes);
        }
    }

    private int readNumber(FileInputStream reader) throws IOException {
        int number = 0;

        char numberSymbol = (char) reader.read();

        while (numberSymbol >= '0' && numberSymbol <= '9') {
            number *= 10;
            number += (int) (numberSymbol - '0');
            numberSymbol = (char) reader.read();
        }

        return number;
    }

    private String readBinaryString(FileInputStream reader) throws IOException {
        StringBuilder currentCodeSB = new StringBuilder();

        char codeSymbol = (char) reader.read();

        while (codeSymbol == '0' || codeSymbol == '1') {
            currentCodeSB.append(codeSymbol);
            codeSymbol = (char) reader.read();
        }

        return currentCodeSB.toString();
    }

    private void makeDecodedOutputArrayList(ArrayList<Byte> outputArrayList) {
        for (int i = 0; i < decodedText.length(); ++i) {
            outputArrayList.add((byte) decodedText.charAt(i));
        }
    }

    private void outputBytes(FileOutputStream writer, ArrayList<Byte> outputArrayList) throws IOException {
        final int MAX_ARRAY_SIZE = 1024;
        int countUsedBytes = 0;

        while (outputArrayList.size() - countUsedBytes >= MAX_ARRAY_SIZE) {
            byte[] outputArray = new byte[MAX_ARRAY_SIZE];
            for (int i = 0; i < MAX_ARRAY_SIZE; ++i) {
                outputArray[i] = outputArrayList.get(countUsedBytes + i);
            }
            writer.write(outputArray);
            countUsedBytes += MAX_ARRAY_SIZE;
        }

        byte[] outputArray = new byte[outputArrayList.size() - countUsedBytes];
        for (int i = 0; i < outputArrayList.size() - countUsedBytes; ++i) {
            outputArray[i] = outputArrayList.get(countUsedBytes + i);
        }
        writer.write(outputArray);
    }

    private void decodingText() {
        decodedText = new StringBuilder();

        CustomBitSet currentBits = new CustomBitSet(0);
        CustomBitSet prefixCode = new CustomBitSet(0);

        for (int bitIndex = 0, symbolIndex = 0; bitIndex < decodeCountBits; ++bitIndex) {

            if (bitIndex % 8 == 0) {
                long nextBits = codedText.charAt(symbolIndex);
                ++symbolIndex;
                int size = Math.min(8, decodeCountBits - bitIndex);
                currentBits = CustomBitSet.fromLong(nextBits, size);
            }

            prefixCode.addBitLast(currentBits.get(bitIndex % 8));

            if (decodeCodeToSymbol.containsKey(prefixCode)) {
                char symbol = decodeCodeToSymbol.get(prefixCode);
                decodedText.append(symbol);
                prefixCode = new CustomBitSet(0);
            }
        }
    }

}


class CustomBitSet implements Comparable<CustomBitSet> {

    private BitSet bitSet;
    private int size;

    public CustomBitSet(int size) {
        this.size = size;
        bitSet = new BitSet();
    }


    public CustomBitSet(String bitSetAsString) {
        this(bitSetAsString.length());

        long bitSetAsLong = 0;
        for (int i = bitSetAsString.length() - 1; i >= 0; --i) {
            bitSetAsLong <<= 1;
            bitSetAsLong += bitSetAsString.charAt(i) - '0';
        }

        long[] longArray = new long[] { bitSetAsLong };
        this.bitSet = BitSet.valueOf(longArray);
    }


    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < this.size; ++i) {
            sb.append(this.bitSet.get(i) ? '1' : '0');
        }
        return sb.toString();
    }

    public static CustomBitSet fromString(String bitSetAsString) {
        return new CustomBitSet(bitSetAsString);
    }

    public static CustomBitSet fromLong(long bitSetAsLong, int size) {
        CustomBitSet customBitSet = new CustomBitSet(size);

        long[] longArray = { bitSetAsLong };
        customBitSet.bitSet = BitSet.valueOf(longArray);

        return customBitSet;
    }


    public void addBitLast(boolean bit) {
        bitSet.set(size, bit);
        ++size;
    }




    public void clear() {
        size = 0;
        bitSet.clear();
    }

    public boolean get(int indexBit) {
        return bitSet.get(indexBit);
    }

    public void set(int indexBit, boolean bit) {
        bitSet.set(indexBit, bit);
    }

    public int compareTo(CustomBitSet otherBitSet) {
        int resultLengthComparing = Integer.compare(this.size, otherBitSet.size);
        int commonLength = Math.min(this.size, otherBitSet.size);

        for (int i = 0; i < commonLength; ++i) {
            int result = Boolean.compare(this.bitSet.get(0), otherBitSet.bitSet.get(0));
            if (result != 0) {
                return result;
            }
        }
        return resultLengthComparing;
    }

    @Override
    public boolean equals(Object otherObject) {
        if (otherObject == null) {
            return false;
        }
        if (!(otherObject instanceof CustomBitSet)) {
            return false;
        }
        CustomBitSet otherBitSet = (CustomBitSet) otherObject;

        if (this.size != otherBitSet.size) {
            return false;
        }

        for (int i = 0; i < this.size; ++i) {
            if (this.bitSet.get(i) != otherBitSet.bitSet.get(i)) {
                return false;
            }
        }

        return true;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        int onePrimaryNumber = 7;
        int otherPrimaryNumber = 13;

        for (int i = 0; i < size; ++i) {
            hash *= onePrimaryNumber;
            if (bitSet.get(i) == true) {
                hash += otherPrimaryNumber;
            }
        }

        return hash;
    }

}

