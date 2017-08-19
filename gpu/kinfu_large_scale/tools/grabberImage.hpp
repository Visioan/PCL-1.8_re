#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class ImageGrabber
{
public:
	ImageGrabber(){};
	ImageGrabber(string sequencedir, string associationstxt) :massociatxtpath(associationstxt), msequencepath(sequencedir){};
	~ImageGrabber(){};
	void getColorDepthImgs(vector<string> &vstrImageFilenamesRGB,vector<string> &vstrImageFilenamesD, vector<double> &vTimestamps)
	{
		LoadImages(massociatxtpath, vstrImageFilenamesRGB, vstrImageFilenamesD, vTimestamps);
	}

	//template<typename T> boost::signals2::connection
	//	Grabber::registerCallback(const boost::function<T> & callback)
	//{
	//	typedef boost::signals2::signal<T> Signal;
	//	if (signals_.find(typeid (T).name()) == signals_.end())
	//	{
	//		std::stringstream sstream;

	//		sstream << "no callback for type:" << typeid (T).name();

	//		PCL_THROW_EXCEPTION(pcl::IOException, "[" << getName() << "] " << sstream.str());

	//	}
	//	Signal* signal = dynamic_cast<Signal*> (signals_[typeid (T).name()]);
	//	boost::signals2::connection ret = signal->connect(callback);

	//	connections_[typeid (T).name()].push_back(ret);
	//	shared_connections_[typeid (T).name()].push_back(boost::signals2::shared_connection_block(connections_[typeid (T).name()].back(), false));
	//	signalsChanged();
	//	return (ret);
	//}

private:
	void LoadImages(const string &strAssociationFilename, vector<string> &vstrImageFilenamesRGB,vector<string> &vstrImageFilenamesD, vector<double> &vTimestamps)
	{
		ifstream fAssociation;
		fAssociation.open(strAssociationFilename.c_str());
		while (!fAssociation.eof())
		{
			string s;
			getline(fAssociation, s);
			if (!s.empty())
			{
				stringstream ss;
				ss << s;
				double t;
				string sRGB, sD;
				ss >> t;
				vTimestamps.push_back(t);
				ss >> sRGB;
				vstrImageFilenamesRGB.push_back(string(msequencepath+"/"+sRGB));
				ss >> t;
				ss >> sD;
				vstrImageFilenamesD.push_back(string(msequencepath + "/" + sD));
			}
		}
	}
private:
	string massociatxtpath,msequencepath;
};