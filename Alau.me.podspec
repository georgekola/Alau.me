Pod::Spec.new do |s|
  s.name             = 'Alau.me'
  s.version          = '2.1.2'
  s.summary          = 'Add referral tracking to your app on the App Store. Create unique (short) download links to track clicks and actual installs.'
  s.description      = <<-DESC
[Alau.me](http://alau.me) is an iOS App Referral Tracking API. It allows you to create short referral links pointing to your app on the App Store and then track the resulting app installs. Kind of like bit.ly, except tailored specifically to apps. But unlike bit.ly, [alau.me](http://alau.me) lets you track not just how many people clicked the link, but how many people went on to download and use your app. 

You can create short links for a specific ad campaign, or you can create a unique link for each of your users, and track user-to-user referrals. Alau.me scales to millions of users and is used by hundreds of apps.
                       DESC
  s.homepage         = 'https://github.com/LumenSpark/Alau.me'
  s.license          = { :type => 'Commercial', :text => 'https://alau.me/home/terms' }
  s.author           = { 'Lumen Spark' => 'developer@lumenspark.com' }
  s.source           = { :git => 'https://github.com/LumenSpark/Alau.me.git', :tag => '2.1.2' }

  s.platform         = :ios, '7.0'
  s.requires_arc     = false

  s.source_files     = 'Alau.me.framework/Headers/*.h'
  s.frameworks       = 'Security'
  s.preserve_paths   = 'Alau.me.framework'
  s.xcconfig         = { 'FRAMEWORK_SEARCH_PATHS' => '$(PODS_ROOT)/Alau.me', 'OTHER_LDFLAGS' => '-framework Alau.me' }
end
