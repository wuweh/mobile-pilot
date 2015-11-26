#import "bluno_impl.h"

@implementation BlunoImpl

- (void) open {
    self.blunoManager = [DFBlunoManager sharedInstance];
    self.blunoManager.delegate = self;
    self.aryDevices = [[NSMutableArray alloc] init];
    //self.lbReady.text = @"Not Ready!";
}

- (void) close {
}

- (void) connect {
	DFBlunoDevice* device = [self.aryDevices objectAtIndex:0];
    if (self.blunoDev == nil)
    {
        self.blunoDev = device;
        [self.blunoManager connectToDevice:self.blunoDev];
    }
    else if ([device isEqual:self.blunoDev])
    {
        if (!self.blunoDev.bReadyToWrite)
        {
            [self.blunoManager connectToDevice:self.blunoDev];
        }
    }
    else
    {
        if (self.blunoDev.bReadyToWrite)
        {
            [self.blunoManager disconnectToDevice:self.blunoDev];
            self.blunoDev = nil;
        }
        
        [self.blunoManager connectToDevice:device];
    }
}

- (void) send : (NSString*) msg {
    if (self.blunoDev.bReadyToWrite) {
        NSData* data = [msg dataUsingEncoding: NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice: data Device: self.blunoDev];
    }
}

- (IBAction) actionSearch : (id) sender {
    [self.aryDevices removeAllObjects];
    //[self.tbDevices reloadData];
    //[self.SearchIndicator startAnimating];
    //self.viewDevices.hidden = NO;
    
    [self.blunoManager scan];
}

- (IBAction) actionReturn : (id) sender {
    //[self.SearchIndicator stopAnimating];
    [self.blunoManager stop];
    //self.viewDevices.hidden = YES;
}

- (IBAction) actionSend : (id) sender {
/*
    [self.txtSendMsg resignFirstResponder];
    if (self.blunoDev.bReadyToWrite)
    {
        NSString* strTemp = self.txtSendMsg.text;
        NSData* data = [strTemp dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:data Device:self.blunoDev];
    }*/
}

- (IBAction) actionDidEnd : (id) sender {
    //[self.txtSendMsg resignFirstResponder];
}

- (void) bleDidUpdateState : (BOOL) bleSupported {
    if(bleSupported) {
        [self.blunoManager scan];
    }
}

- (void) didDiscoverDevice : (DFBlunoDevice*) dev {
    BOOL bRepeat = NO;
    for (DFBlunoDevice* bleDevice in self.aryDevices)
    {
		BOOL isBluno = [bleDevice.name isEqualToString: @"bluno"] || [bleDevice.identifier isEqualToString: @"bluno"];
        if (isBluno && [bleDevice isEqual:dev])
        {
            bRepeat = YES;
            break;
        }
    }
    if (!bRepeat)
    {
        [self.aryDevices addObject:dev];
    }
    //[self.tbDevices reloadData];

	[self connect];
}

- (void) readyToCommunicate : (DFBlunoDevice*) dev {
    self.blunoDev = dev;
    //self.lbReady.text = @"Ready!";
}

- (void) didDisconnectDevice : (DFBlunoDevice*) dev {
    //self.lbReady.text = @"Not Ready!";
}

- (void) didWriteData : (DFBlunoDevice*) dev {
}

- (void) didReceiveData : (NSData*) data Device : (DFBlunoDevice*) dev {
    //self.lbReceivedMsg.text = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

#pragma mark- TableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSInteger nCount = [self.aryDevices count];
    return nCount;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *MyIdentifier = @"ScanDeviceCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:MyIdentifier];
    
    if (cell == nil)
    {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
        {
            [[NSBundle mainBundle] loadNibNamed:@"CellDeviceList" owner:self options:nil];
        }
        else
        {
            
        }
        
        //cell = self.cellDevices;
	}
    
    UILabel* lbName             = (UILabel*)[cell viewWithTag:1];
    UILabel* lbUUID             = (UILabel*)[cell viewWithTag:2];
    DFBlunoDevice* peripheral   = [self.aryDevices objectAtIndex:indexPath.row];
    
    lbName.text = peripheral.name;
    lbUUID.text = peripheral.identifier;
    
    return cell;
    
}


#pragma mark- TableView Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    DFBlunoDevice* device = [self.aryDevices objectAtIndex:indexPath.row];
    if (self.blunoDev == nil)
    {
        self.blunoDev = device;
        [self.blunoManager connectToDevice:self.blunoDev];
    }
    else if ([device isEqual:self.blunoDev])
    {
        if (!self.blunoDev.bReadyToWrite)
        {
            [self.blunoManager connectToDevice:self.blunoDev];
        }
    }
    else
    {
        if (self.blunoDev.bReadyToWrite)
        {
            [self.blunoManager disconnectToDevice:self.blunoDev];
            self.blunoDev = nil;
        }
        
        [self.blunoManager connectToDevice:device];
    }
    //self.viewDevices.hidden = YES;
    //[self.SearchIndicator stopAnimating];
}

@end
