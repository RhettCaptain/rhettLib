using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace SrvRob
{
    class TxtHelper
    {
        private string path;
        private FileMode mode;

        public TxtHelper(string pPath,FileMode pMode = FileMode.OpenOrCreate)
        {
            path = pPath;
            mode = pMode;
        }

        public void setPath(string pPath)
        {
            path = pPath;
        }

        public void setMode(FileMode pMode)
        {
            mode = pMode;
        }

        public string read()
        {
            StreamReader sr = new StreamReader(path, Encoding.Default);
            string content = "";
            String line;
            while ((line = sr.ReadLine()) != null)
            {
                content += (line.ToString()+"\n");
            }
            return content;
        }

        public string readLine()
        {
            StreamReader sr = new StreamReader(path, Encoding.Default);
            String line = sr.ReadLine();
            return line.ToString();
        }

        public void write(string content)
        {
            FileStream fs = new FileStream(path, mode);
            StreamWriter sw = new StreamWriter(fs);
            sw.Write(content);
            sw.Flush();
            sw.Close();
            fs.Close();
        }
    }
}
