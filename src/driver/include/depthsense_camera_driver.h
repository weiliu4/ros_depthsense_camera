#include <DepthSense.hxx>

#include <ros/ros.h>

#include <list>

using namespace std;

class DepthSenseDriver
{
public:

    struct NodeInfo
    {
        DepthSense::Node node;
        int32_t sampleCount;
        int32_t totalSampleCount;
        int32_t droppedSampleCount;
        int32_t width;
        int32_t height;
        float range;
    };

    DepthSenseDriver();
    ~DepthSenseDriver();

    void init();
    void release();

    void run();

    void mySigintHandler(int sig);

private:
    void onDeviceAdded(DepthSense::Context context, DepthSense::Device device);
    void onDeviceRemoved(DepthSense::Context context, DepthSense::Device device);

    void onNodeAdded(DepthSense::Device device, DepthSense::Node node);
    void onNodeRemoved(DepthSense::Device device, DepthSense::Node node);

    NodeInfo* findInfo(DepthSense::Node node);

    void onNewDepthNodeSampleReceived(DepthSense::DepthNode node, DepthSense::DepthNode::NewSampleReceivedData data);
    void onNewColorNodeSampleReceived(DepthSense::ColorNode node, DepthSense::ColorNode::NewSampleReceivedData data);

private:
    DepthSense::Context _context; ///< DepthSense context

    std::list<DepthSense::Device> _devices;
    std::list<NodeInfo*> _nodeInfos;

    //DepthSense::ColorNode _color; ///< DepthSense color node
    //DepthSense::DepthNode _depth; ///< DepthSense depth node

    bool _initialized;
    bool _streaming;
    bool _error;
};

