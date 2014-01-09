require 'rb-inotify'
require 'rest-client'
require 'date'

notifier = INotify::Notifier.new
last_alarm = nil

notifier.watch("camera", :create) do |event|
  now = DateTime.now
  if !last_alarm || now.to_time - last_alarm.to_time > 10 # in seconds
    last_alarm = now
    # Send a message to the openHAB server
    #RestClient.put 'http://ensipc03.imag.fr:8080/rest/items/Mouvement_Detector/state', "ON", {:content_type => 'text/plain'}
    #RestClient.put 'http://localhost:8080/rest/items/Mouvement_Detector/state', "ON", {:content_type => 'text/plain'}
    # Send a message to a machine connected to the VPN network
    #RestClient.get 'http://localhost:3000/presence'
  end
  # Delete the file if the presence is normal
  if now.hour < 20 && now.hour >= 7 && now.cwday <= 5
    File.delete("camera/"+event.name)
    puts "#{event.name} has been deleted after create."
  else
    puts "#{event.name} is now in camera folder!"
  end
end

puts "INotifier correctly instancied"
notifier.run
puts "Oops ! The program terminated." # Must never happen
