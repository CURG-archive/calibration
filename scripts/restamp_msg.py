#!/usr/bin/python
import rospy
import ipdb

class MessageRestamper():
    def __init__(self):
        param_name = rospy.search_param('restamped_topics')
        print "Param name"
        print param_name
        self.topic_names = rospy.get_param(param_name)


        self.subscribers = {}
        self.publishers = {}
        self.setup_topics()

    def get_msg_class_dict(self, topic_names):
        all_topics = dict(rospy.get_published_topics())
        msg_class_dict = {}
        for topic_name in topic_names:
            class_type_string = all_topics[topic_name]
            topic_package_name, topic_class_name  =  class_type_string.split('/')
            topic_package = eval('__import__("%s.msg"%(topic_package_name), fromlist=[topic_class_name], level=-1)')
            msg_class = eval('topic_package.%s'%(topic_class_name))
            msg_class_dict[topic_name] = msg_class
        return msg_class_dict


    def restamp_msg(self, msg, topic_name):
        msg.header.stamp = rospy.Time.now()
        self.publishers[topic_name].publish(msg)

    def setup_topics(self):
        msg_class_dict = self.get_msg_class_dict(self.topic_names)
        for topic_name, topic_class in msg_class_dict.iteritems():
            self.publishers[topic_name] = rospy.Publisher('/restamped%s'%(topic_name), topic_class)

            self.subscribers[topic_name] = rospy.Subscriber(topic_name, topic_class, self.restamp_msg, topic_name)

def main():
    rospy.init_node('test')
    mr = MessageRestamper()
    rospy.spin()





if __name__ == "__main__":
    main()


