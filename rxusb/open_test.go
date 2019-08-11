package rxusb

import (
	"testing"

	"github.com/google/gousb"
	"github.com/stretchr/testify/suite"
)

type OpenSuite struct {
	suite.Suite
}

func TestOpenSuite(t *testing.T) {
	suite.Run(t, new(OpenSuite))
}

func (suite *OpenSuite) TestOpen() {
	ctx := gousb.NewContext()
	suite.Require().NotNil(ctx)
	defer ctx.Close()

	rx_VendorID := gousb.ID(5824)
	rx_ProductID := gousb.ID(1500)
	dev, err := ctx.OpenDeviceWithVIDPID(rx_VendorID, rx_ProductID)

	suite.Require().NoErrorf(err, "%+v", err)
	suite.Require().NotNil(dev)
	defer dev.Close()

	err = dev.SetAutoDetach(true)
	suite.Require().NoError(err)

	cfg, err := dev.Config(1)
	suite.Require().NoError(err)

	intf, err := cfg.Interface(0, 0)
	suite.Require().NoError(err)
	suite.Require().NotNil(intf)

	panic(intf.Setting.Endpoints)

	ep, err := intf.OutEndpoint(0x81)
	suite.Require().NoError(err)

	_, err = ep.Write([]byte{1, 63, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0})
	suite.Require().NoError(err)
	suite.Require().Nil(ep)
}
