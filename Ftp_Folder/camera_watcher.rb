require 'rb-inotify' # Gem to check changes on folders and files
require 'rest-client' # Gem to make HTTP requests
require 'date' # Gem to manipulate time

notifier = INotify::Notifier.new
last_alarm = nil

notifier.watch("camera", :create) do |event|
  # Called each time an image is sent
  now = DateTime.now
  if !last_alarm || now.to_time - last_alarm.to_time > 10 # in seconds
    # Do not send alarm if it has already been sent in the 10 previous seconds
    last_alarm = now
    puts "Alarm !"
    # Can send a message directly to the openHAB server
    #RestClient.put 'http://ensipc03.imag.fr:8080/rest/items/Mouvement_Detector/state', "ON", {:content_type => 'text/plain'}
    # Send a message to a machine connected to the VPN network -> here itself. The server redistribute the message to OpenHAB
    RestClient.get 'http://localhost/presence'
  end
  # Delete the file if the presence is normal
  if now.hour < 20 && now.hour >= 7 && now.cwday <= 5
    File.delete("camera/"+event.name)
    puts "#{event.name} has been deleted after create."
  else
    puts "#{event.name} is kept in camera folder."
  end
end

puts "INotifier correctly instancied"
notifier.run
puts "Oops ! The program terminated." # Must never happen
