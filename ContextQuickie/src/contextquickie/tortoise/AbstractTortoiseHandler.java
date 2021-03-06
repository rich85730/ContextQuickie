package contextquickie.tortoise;

import org.eclipse.core.commands.AbstractHandler;
import contextquickie.preferences.TortoisePreferenceConstants;

/**
 * Base class for all tortoise command handlers.
 */
public abstract class AbstractTortoiseHandler extends AbstractHandler
{
  /**
   * The preferences of the current instance.
   */
  private TortoisePreferenceConstants preferenceConstants;

  /**
   * @return The preference constants.
   */
  public TortoisePreferenceConstants getPreferenceConstants()
  {
    return this.preferenceConstants;
  }

  /**
   * @param value The preference constants.
   */
  public void setPreferenceConstants(TortoisePreferenceConstants value)
  {
    this.preferenceConstants = value;
  }
}
