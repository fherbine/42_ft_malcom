Vagrant.configure("2") do |config|
	config.vm.box = "generic/centos8"
	config.vm.synced_folder ".", "/tmp/ft_malcom"

	config.vm.define "blackhat" do |c|
		c.vm.box = "generic/centos8"
		c.vm.hostname = "blackhat"
		c.vm.network "private_network", ip: "192.168.42.2", name: "vboxnet0"

		c.vm.provider "virtualbox" do |vb|
			vb.customize ["modifyvm", :id, "--natdnsproxy1", "on"]
			vb.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
		end
	end

	config.vm.define "target1" do |c|
		c.vm.box = "generic/centos8"
		c.vm.hostname = "target1"
		c.vm.network "private_network", ip: "192.168.42.3", name: "vboxnet0"

		c.vm.provider "virtualbox" do |vb|
			vb.customize ["modifyvm", :id, "--natdnsproxy1", "on"]
			vb.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
		end
	end
	
	config.vm.define "target2" do |c|
		c.vm.box = "generic/centos8"
		c.vm.hostname = "target2"
		c.vm.network "private_network", ip: "192.168.42.4", name: "vboxnet0"

		c.vm.provider "virtualbox" do |vb|
			vb.customize ["modifyvm", :id, "--natdnsproxy1", "on"]
			vb.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
		end
	end
end
